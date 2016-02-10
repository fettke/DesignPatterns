#include <iostream>
#include <memory>
#include <functional>

static void flyWithWings()
{
    std::cout << "I'm flying!!" << std::endl;
}

static void flyNoWay()
{
    std::cout << "I can't fly" << std::endl;
}

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


static void quack()
{
    std::cout << "Quack" << std::endl;
}

static void muteQuack()
{
    std::cout << "<< Silence >> " << std::endl;
}

static void squeak()
{
    std::cout << "Squeak" << std::endl;
}


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
        : Duck(&quack, &flyWithWings)
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
        : Duck(&quack, &flyNoWay)
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
        : Duck(&muteQuack, FlyWithRocket())
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
}
