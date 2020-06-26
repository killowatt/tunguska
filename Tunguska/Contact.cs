using Microsoft.Xna.Framework;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Tunguska
{
    abstract class Contact
    {
        public Vector3 Position = new Vector3(0.0f);
        public bool IsDestroyed = false;

        public abstract void Update(float deltaTime);
    }
}
