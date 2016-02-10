#include <iostream>
#include <memory>
#include <functional>

class FlyWithWings
{
public:
    static void fly()
    {
        std::cout << "I'm flying!!" << std::endl;
    }
};

class FlyNoWay
{
public:
    static void fly()
    {
        std::cout << "I can't fly" << std::endl;
    }
};

class FlyWithRocket
{
public:
    FlyWithRocket()
        : m_Energy(3)
    { }

    void operator() ()
    {
        if (m_Energy > 0)
        {
            fly_with_rocket();
            --m_Energy;
        }
        else
        {
            fly_out_of_energy();
        }
    }

private:
    void fly_with_rocket()
    {
        std::cout << "I'm flying with a rocket!" << std::endl;
    }
    void fly_out_of_energy()
    {
        std::cout << "I'm out of energy" << std::endl;
    }

    unsigned int m_Energy;
};


class Quack
{
public:
    static void quack()
    {
        std::cout << "Quack" << std::endl;
    }
};

class MuteQuack
{
public:
    static void quack()
    {
        std::cout << "<< Silence >> " << std::endl;
    }
};

class Squeak
{
public:
    static void quack()
    {
        std::cout << "Squeak" << std::endl;
    }
};


class Duck
{
public:
    typedef std::function<void(void)> QUACK;
    typedef std::function<void(void)> FLY;

    Duck(const QUACK &q, const FLY &f)
        : m_Quack(q), m_Fly(f)
    {}

    virtual ~Duck()
    {}

    void performFly()
    {
        m_Fly();
    }

    void performQuack()
    {
        m_Quack();
    }

    void swim()
    {
        std::cout << "All ducks float, even decoys!" << std::endl;
    }

    virtual void display() = 0;

protected:
    QUACK m_Quack;
    FLY m_Fly;

private:
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;
};

class MallardDuck : public Duck
{
public:
    MallardDuck()
        : Duck(&Quack::quack, &FlyWithWings::fly)
    {
    }

    void display()
    {
        std::cout << "I'm a real Mallard duck!" << std::endl;
    }
};

class ModelDuck : public Duck
{
public:
    ModelDuck()
        : Duck(&Quack::quack, &FlyNoWay::fly)
    {
    }

    void display()
    {
        std::cout << "I'm a model duck" << std::endl;
    }
};

class RubberDuck : public Duck
{
public:
    RubberDuck()
        : Duck(&MuteQuack::quack, FlyWithRocket())
    {}

    void display()
    {
        std::cout << "I'm a rubber duck" << std::endl;
    }
};

int main(void)
{
    MallardDuck d1;
    d1.display();
    d1.performQuack();
    d1.performFly();

    ModelDuck d2;
    d2.display();
    d2.performQuack();
    d2.performFly();

    RubberDuck d3;
    d3.display();
    d3.performQuack();
    d3.performFly();
    d3.performFly();
    d3.performFly();
    d3.performFly();

    //std::shared_ptr<FlyBehaviour> new_fb(new FlyRocketPowered());
    //model->setFlyBehaviour(new_fb);
    //model->performFly();
}