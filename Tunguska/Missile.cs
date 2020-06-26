using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;

namespace Tunguska
{
    class Missile : Contact
    {
        public float TopSpeed;
        public Contact Target;

        Vector3 lastDirection;

        public Missile()
        {
            TopSpeed = 6.0f;
            Target = null;

            lastDirection = new Vector3(1.0f, 0.0f, 0.0f);
        }

        public override void Update(float deltaTime)
        {
            if (Target == null)
            {
                Position += lastDirection * TopSpeed * deltaTime;
                return;
            }

            Vector3 direction = Target.Position - Position;
            direction.Normalize();

            Position += direction * TopSpeed * deltaTime;
            lastDirection = direction;

            if (Vector3.Distance(Target.Position, Position) < 1.0f)
            {
                IsDestroyed = true;
                Target.IsDestroyed = true;
            }
        }

    }
}
