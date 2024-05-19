#include "trem.h"
#include <QtCore>




sem_t RegCritica0,RegCritica1,RegCritica2,RegCritica3,RegCritica4,RegCritica5,RegCritica6;
//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    movimento = true;

    sem_init(&RegCritica0,0,0);
    sem_init(&RegCritica1,0,1);
    sem_init(&RegCritica2,0,0);
    sem_init(&RegCritica3,0,1);
    sem_init(&RegCritica4,0,0);
    sem_init(&RegCritica5,0,0);
    sem_init(&RegCritica6,0,0);
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if(movimento){
                if (y == 30 && x <510){
                    if(x == 490){

                        sem_wait(&RegCritica2);
                        sem_wait(&RegCritica0);

                    }
                    x+=10;
                }
                else if (x == 510 && y < 150){
                    y+=10;
                }
                else if (x > 240 && y == 150){
                    if(x == 490){
                        sem_post(&RegCritica0);
                    }
                    if(x == 370){
                        sem_wait(&RegCritica1);
                    }
                    if(x == 330){
                        sem_post(&RegCritica2);
                    }
                    x-=10;
                }
                else{
                    if(y == 130){
                        sem_post(&RegCritica1);
                    }
                    y-=10;
                }
                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            }
        case 2: //Trem 2
            if(movimento){
                if (y == 30 && x <780){
                    if( x == 510){
                        sem_post(&RegCritica0);
                    }
                    x+=10;
                }
                else if (x == 780 && y < 150){
                    if(y == 130){
                        sem_wait(&RegCritica4);
                    }
                    y+=10;
                }
                else if (x > 510 && y == 150){
                    if(x == 640){
                        sem_wait(&RegCritica3);
                    }
                    if(x == 600){
                        sem_post(&RegCritica4);
                    }
                    if(x == 530){
                        sem_wait(&RegCritica0);
                    }
                    x-=10;
                }
                else{
                    if(y == 130){
                        sem_post(&RegCritica3);
                    }
                    y-=10;
                }
                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            }
        case 3: //Trem 1
            if(movimento){
                if (y == 150 && x <350){
                    if(x == 220){
                        sem_wait(&RegCritica1);
                    }
                    if(x == 330){
                        sem_wait(&RegCritica5);
                    }
                    x+=10;
                }
                else if (x == 350 && y < 270){
                    if(y == 170){
                        sem_post(&RegCritica1);
                    }
                    y+=10;
                }
                else if (x > 100 && y == 270){
                    if(x == 350){
                        sem_post(&RegCritica5);
                    }
                    x-=10;
                }
                else{
                    y-=10;
                }
                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            }
        case 4: //Trem 2
            if(movimento){
                if (y == 150 && x <620){
                    if(x == 350){
                        sem_post(&RegCritica5);
                    }
                    if(x == 490){
                        sem_wait(&RegCritica6);
                        sem_wait(&RegCritica3);
                    }
                    if(x == 530){
                        sem_post(&RegCritica2);
                    }
                    x+=10;
                }
                else if (x == 620 && y < 270){
                    if( y == 170 ){
                        sem_post(&RegCritica3);
                    }
                    y+=10;
                }
                else if (x > 350 && y == 270){
                    if(x == 600){
                        sem_post(&RegCritica6);
                    }
                    if(x == 370){
                        sem_wait(&RegCritica2);
                        sem_wait(&RegCritica5);
                    }
                    x-=10;
                }
                else{
                    y-=10;
                }
                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            }
        case 5: //Trem 2
            if(movimento){
                if (y == 150 && x <890){
                    if( x == 640){
                        sem_post(&RegCritica6);
                    }
                    if(x == 800){
                        sem_post(&RegCritica4);
                    }
                    x+=10;
                }
                else if (x == 890 && y < 270){
                    y+=10;
                }
                else if (x > 620 && y == 270){
                    if (x == 640){
                        sem_wait(&RegCritica6);
                    }
                    x-=10;
                }
                else{
                    if(y == 170){
                        sem_wait(&RegCritica4);
                    }
                    y-=10;
                }
                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            }

        default:
            break;
        }
        msleep(velocidade);
    }
    sem_destroy(&RegCritica0);
    sem_destroy(&RegCritica1);
    sem_destroy(&RegCritica2);
    sem_destroy(&RegCritica3);
    sem_destroy(&RegCritica4);
    sem_destroy(&RegCritica5);
    sem_destroy(&RegCritica6);

}

void Trem::setVel(int val){
    if(val == 230 ){
        this->setMov(false);
    }else{
        this->setMov(true);
    }
    this->velocidade = val;
}

void Trem::setMov(bool val){
    this->movimento = val;
}




