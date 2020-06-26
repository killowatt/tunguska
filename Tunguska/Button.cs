using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Tunguska
{

    public delegate void OnPressed();

    class Button : Interactable
    {
        Texture2D buttonTexture;
        Texture2D pressedTexture;

        bool pressed;

        public event OnPressed OnPressed;

        public Button(ContentManager content)
        {
            Size = new Vector2(36, 36);

            buttonTexture = content.Load<Texture2D>("launchbutton");
            pressedTexture = content.Load<Texture2D>("launchbuttonpressed");
        }

        public void Update(GameTime gameTime)
        {
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            if (!pressed)
                spriteBatch.Draw(buttonTexture, Position, Color.White);
            else
                spriteBatch.Draw(pressedTexture, Position, Color.White);
        }

        public override void OnClick()
        {
            pressed = true;
            OnPressed?.Invoke();
        }

        public override void OnRelease()
        {
            pressed = false;
        }
    }
}
