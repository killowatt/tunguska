using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Tunguska
{
    abstract class Interactable
    {
        public Vector2 Position;
        public Vector2 Size;

        public virtual void OnClick() { }

        public virtual void OnScroll(bool direction) { }

        public virtual void OnRelease() { }
    }
}
