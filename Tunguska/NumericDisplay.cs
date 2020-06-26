using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Tunguska
{
    class NumericDisplay
    {
        public int NumberToDisplay;

        public Vector2 ScreenPosition;

        Texture2D backgroundTexture;
        Texture2D numberTexture;

        public NumericDisplay(ContentManager content)
        {
            NumberToDisplay = 0;

            backgroundTexture = content.Load<Texture2D>("numericdisplay");
            numberTexture = content.Load<Texture2D>("numbers");
        }

        public void Update(float deltaTime)
        {
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(backgroundTexture, ScreenPosition, Color.White);


            string numbers = NumberToDisplay.ToString();
            int back = Math.Min(numbers.Length, 4);

            int startingCharacter = Math.Max(numbers.Length - 4, 0);
            for (int i = startingCharacter; i < numbers.Length; i++)
            {
                int number = numbers[i] - 48;

                Rectangle spriteSource = new Rectangle(6 * number, 0, 6, 14);
                Vector2 position = new Vector2(1 - back * 7, 2);
                position.X += backgroundTexture.Width - 2;
                spriteBatch.Draw(numberTexture, position + ScreenPosition, spriteSource, Color.White);
                back--;
            }
        }
    }
}
