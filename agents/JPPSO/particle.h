#ifndef PARTICLE_H
#define PARTICLE_H

class particle
{
   private:
      PSOCoeffientType C0, C2, C3, C4;
      PSOIdType id;
      PSOVelocityType velocity;
      PSOPositionType position;

   protected:

   public:
      particle();
      ~particle();

      void setC0(PSOCoefficientType C0)
         { this->C0 = C0; }
      void setC1(PSOCoefficientType C1)
         { this->C1 = C1; }
      void setC2(PSOCoefficientType C2)
         { this->C2 = C2; }
      void setC3(PSOCoefficientType C3)
         { this->C3 = C3; }
      void setId(PSOIdType id)
         { this->id = id; }
      void setVelocity(PSOVelocityType)
         { this->velocity = velocity; }
      void setPosition(PSOPositionType)
         { this->position = position; }

      PSOCoefficientType getC0() const
         { return this->C0; }
      PSOCoefficientType getC1() const
         { return this->C1; }
      PSOCoefficientType getC2() const
         { return this->C2; }
      PSOCoefficientType getC3() const
         { return this->C3; }
      PSOIdType getId() const
         { return this->id; }
      PSOVelocityType getVelocity() const
         { return this->velocity; }
      PSOPositionType getPosition() const
         { return this->position; }
 
};

particle::particle()
{
   this->C0 = 0;
   this->C1 = 0;
   this->C2 = 0;
   this->C3 = 0;
   this->position = 0;
   this->velocity = 0;
   this->id = 0;
}

#endif

