#ifndef ENTITY_H
#define ENTITY_H
#include<QPainter>
class Entity
{
public:
    Entity(){}
    virtual void update()=0;//更新状态用
    virtual void draw(QPainter* painter)=0;//绘制函数

    inline bool isActive()const{return active;}
    inline void destroy(){active =false;}//摧毁
    inline int type()const{return m_type;}
    inline void setType(int type){m_type =type;}
private:
    bool active =true;
    int m_type=0;
};//实体的虚模板

#endif // ENTITY_H
