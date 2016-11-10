#include "bullet.hpp"
#include <iostream>
#define lift_side 5
#define right_side 795
#define up_side 5
#define down_side 595
#define t 0.0005
/*void bullet::Put_Bullet(int x, int y, int vx, int vy){
	bullet bullet;
	CircleShape bullet_shape(5);
	bullet_shape.setFillColor(Color::Green);
	bullet.x = x;
	bullet.y = y;
	bullet.vx = vx;
	bullet.vy = vy;
	bullet_shape.setPosition(x, y);
 
 }*/

void Bullet::horizontal_collide(){
    horizontal_collision = true;
}
void Bullet::vertical_collide(){
    vertical_collsion = true;
}
void Bullet::reset_collision(){
    horizontal_collision = false;
    vertical_collsion = false;
}

void Bullet::update(sf::Image &image)
{
  //  float elapsed_time = elapsed.asSeconds();
    //update position
    
    //stay in window
    current_position=this->getPosition();
    if (current_position.x <= lift_side||current_position.x>=right_side){
        dx = -dx;
    }
    if (current_position.y >= down_side||current_position.y<=up_side){
        dy = -dy;
    }

    
          if (horizontal_collision)
        {
            dy = -dy;
        }
        if (vertical_collsion)
        {
            dx = -dx;
        }
    
    collsion_check(image);
    
        this->move(dx,dy);
        
    
    
        
        
}


void Bullet::collsion_check(sf::Image image){
    
        float r=this->getRadius();

        sf::Vector2f p = this->getPosition();
    /*
        // 上
        
        up_point.x=p.x;
        up_point.y=p.y-r;
        
        //下
        
        down_point.x=p.x;
        down_point.y=p.y+r;
        //左
    
        left_point.x=p.x-r;
        left_point.y=p.y;
        
        
        
        //右
        right_point.x=p.x+r;
        right_point.y=p.y;
    */
    
    if (image.getPixel(p.x,p.y).toInteger() == 4278190335) {
        if (dy>0) {
            dy=-dy;
        }
    }
    
    if (image.getPixel(p.x,p.y).toInteger() == 4261413119) {
        if (dy<0) {
            dy=-dy;
        }

    }
    
    if (image.getPixel(p.x,p.y).toInteger() == 4244635903) {
        if (dx<0) {
            dx=-dx;
        }

    }
    
    if (image.getPixel(p.x,p.y).toInteger() == 4227858687) {
        if (dx>0) {
            dx=-dx;
        }

    }
        
    
}



void Bullet::Draw_Bullet(sf::RenderWindow &window){
//    Get_Next_Position();
 //   this->setPosition(x, y);
   
}
void Bullet::Run_Bullet(){
    CircleShape bullet_shape;
    bullet_shape.setRadius(5);
    bullet_shape.setFillColor(sf::Color::Green);
    sf::RenderWindow window(sf::VideoMode(800, 600), "bullet!");
    sf::Clock clock;
    sf::Time run_time=sf::seconds(t);
    while (window.isOpen())
    {
        if (clock.getElapsedTime() >= run_time){
 //           bullet_shape.setPosition(x, y);
            window.clear();
            window.draw(bullet_shape);
            window.display();
            //bullet.Get_Next_Position(bullet.x, bullet.y, bullet.vx, bullet.vy);
            //	printf("%d,%d,%d,%d,%f\n", bullet.x, bullet.y, bullet.vx, bullet.vy, t);
            clock.restart();
        }
        
    }
}

