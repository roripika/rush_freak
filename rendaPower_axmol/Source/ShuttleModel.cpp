#include "ShuttleModel.h"
#include "axmol.h"
#include "audio/AudioEngine.h"
#include "common/SoundDef.h"

using namespace ax;

const unsigned long ShuttleModel::CHARGE_ADD = 10;
const unsigned long ShuttleModel::CHARGE_MAX = 1500;
const unsigned long ShuttleModel::ACCELERATION = 2;
const unsigned long ShuttleModel::SPEED_MAX = 15;
const float ShuttleModel::ENERGY_CONVERT = 0.25f;

ShuttleModel::ShuttleModel()
:m_Energy(0)
,m_Speed(0)
,m_RocketSprite(nullptr)
,m_runAcceleration(false)
,m_takeoffCallback(nullptr)
,m_smork(nullptr)
{
}

ShuttleModel::~ShuttleModel()
{
}

bool ShuttleModel::init()
{
    if(!Node::init())
    {
        return false;
    }

    // Audio Engine preloading is not strictly necessary but good for cache
    AudioEngine::preload(DEF_SE_TAKEOFF);
    AudioEngine::preload(DEF_SE_RUSH);
    AudioEngine::preload(DEF_SE_ROCKET_READY);
    
    if(this->m_RocketSprite) this->m_RocketSprite->removeFromParent();
    this->m_RocketSprite = Sprite::create("base/rocket.png");
    this->addChild(this->m_RocketSprite,10);
    
    this->setContentSize(this->m_RocketSprite->getContentSize());
    this->setAnchorPoint(Vec2(0.5f,0.5f));
    
    this->m_RocketSprite->setPosition(Vec2(this->getContentSize().width * 0.5f,
                                          this->getContentSize().height * 0.5f));

    this->scheduleUpdate();
    
    this->m_smork = ParticleSmoke::create();
    
    this->m_smork->setTexture(Director::getInstance()->getTextureCache()->addImage("base/kumo.png"));
    this->m_smork->setAngle(270);
    this->m_smork->setAngleVar(60);
    this->m_smork->setTotalParticles(50);
    this->m_smork->setSpeed(100);
    this->m_smork->setSpeedVar(30);
    this->m_smork->setGravity(Vec2(0,50));
    this->m_smork->setSourcePosition(Vec2::ZERO);
    this->m_smork->setPosVar(Vec2(20,0));
    this->m_smork->setLife(1.5f);
    this->m_smork->setLifeVar(3.0f);
    this->m_smork->setStartSize(50);
    this->m_smork->setEndSize(150);
    this->m_smork->setStartColor(Color4F(Color4B(0xFF, 0xFF, 0xFF, 0xFF)));
    this->m_smork->setEndColor(Color4F(Color4B(0x0, 0x0, 0x0, 0x0)));
    this->m_smork->setVisible(false);
    this->m_smork->setPosition(this->m_RocketSprite->getPosition() - Vec2(0,this->m_RocketSprite->getContentSize().height * 0.5f));
    this->addChild(this->m_smork,0);
    return true;
}

void ShuttleModel::chargeEnergy()
{
    if(this->m_Energy < CHARGE_MAX)
    {
        AudioEngine::play2d(DEF_SE_RUSH);
        
        this->m_Energy += CHARGE_ADD;
        if(this->m_Energy > CHARGE_MAX)
        {
            this->m_Energy = CHARGE_MAX;
        }
    }
}

void ShuttleModel::resetParam()
{
    this->m_Energy = 0;
    this->m_Speed = 0;
    
    m_runAcceleration = false;
    this->m_smork->setGravity(Vec2(0,50));
    this->m_smork->stopSystem();
}

void ShuttleModel::rocketStart(std::function<void()> takeoffCallback)
{
    AudioEngine::play2d(DEF_SE_ROCKET_READY);
    
    //煙吹き出し
    this->m_smork->setVisible(true);
    this->m_smork->resetSystem();

    Vector<FiniteTimeAction*> actions;
    for(int index = 0; index < 30; index++)
    {
        actions.pushBack(MoveBy::create(0.03125f, Vec2(10,0)));
        actions.pushBack(MoveBy::create(0.0625f, Vec2(-20,0)));
        actions.pushBack(MoveBy::create(0.03125f, Vec2(10,0)));
    }
    
    actions.pushBack(CallFunc::create(AX_CALLBACK_0(ShuttleModel::takeoff, this)));
    this->runAction(Sequence::create(actions));

    this->m_takeoffCallback = takeoffCallback;
}

void ShuttleModel::takeoff()
{
    AudioEngine::play2d(DEF_SE_TAKEOFF);

    this->m_runAcceleration = true;
    this->m_smork->setGravity(Vec2::ZERO);
    
    if(this->m_takeoffCallback)
    {
        this->m_takeoffCallback();
    }
}

void ShuttleModel::acceleration()
{
    if(m_Speed <= SPEED_MAX)
    {
        m_Speed += ACCELERATION;
    }
}

void ShuttleModel::slowdown()
{
    if(m_Speed >= 0)
    {
        m_Speed -= ACCELERATION;
    }
    if(m_Speed < 0) m_Speed = 0;
}

void ShuttleModel::update(float delta)
{
    Node::update(delta);
    
    if(m_runAcceleration)
    {
        this->setPosition(this->getPosition() + Vec2(0, (float)m_Speed));
        this->energyConsumption();
        if(this->m_Energy > 0)
        {
            this->acceleration();
        }
        else
        {
            if(this->m_smork->isActive())
            {
                this->m_smork->stopSystem();
            }
            this->slowdown();
        }
    }
}

void ShuttleModel::energyConsumption()
{
    if(this->m_Energy > 0) this->m_Energy -= (long)(m_Speed * ENERGY_CONVERT);
    if(this->m_Energy < 0) this->m_Energy = 0;
}

