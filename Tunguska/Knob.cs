using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;

namespace Tunguska
{
    class Knob : Interactable
    {
        public int CurrentValue;

        public int MinimumValue;
        public int MaximumValue;

        public Texture2D KnobTexture;
        public Vector2 FrameSize;
        public int FrameCount = 8;

        public Knob(ContentManager content)
        {
            KnobTexture = content.Load<Texture2D>("knob");

            MinimumValue = -32;
            MaximumValue = 32;
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            Rectangle spriteFrame = new Rectangle(
                (int)FrameSize.X * (Math.Abs(CurrentValue) % FrameCount), 0,
                (int)FrameSize.X, (int)FrameSize.Y);

            spriteBatch.Draw(KnobTexture, Position, spriteFrame, Color.White);
        }

        public override void OnScroll(bool direction)
        {
            if (direction)
                CurrentValue++;
            else
                CurrentValue--;

            if (CurrentValue > MaximumValue)
                CurrentValue = MaximumValue;
            else if (CurrentValue < MinimumValue)
                CurrentValue = MinimumValue;
        }
    }
}
