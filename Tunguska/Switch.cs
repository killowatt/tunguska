using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Tunguska
{
    class Switch : Interactable
    {
        public bool SwitchState;

        Texture2D baseTexture;
        Texture2D flickerUpTexture;
        Texture2D flickerDownTexture;

        public Switch(ContentManager content)
        {
            SwitchState = false;

            Size = new Vector2(8, 16);

            baseTexture = content.Load<Texture2D>("switchbase");
            flickerUpTexture = content.Load<Texture2D>("switchup");
            flickerDownTexture = content.Load<Texture2D>("switchdown");
        }

        public void Update(GameTime gameTime)
        {
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(baseTexture, Position, Color.White);

            Vector2 flickerPosition = Position;
            if (SwitchState)
            {
                flickerPosition.Y -= 8;
                spriteBatch.Draw(flickerUpTexture, flickerPosition, Color.White);
            }
            else
            {
                flickerPosition.Y += 2;
                spriteBatch.Draw(flickerDownTexture, flickerPosition, Color.White);
            }
                    

        }

        public override void OnClick()
        {
            SwitchState = !SwitchState;
        }

    }
}
