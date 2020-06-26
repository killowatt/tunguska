using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Tunguska
{
    public class Tunguska : Game
    {
        static readonly int resw = 1280;
        static readonly int resh = 720;
        static readonly float resfac = resw / 640.0f;


        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        RenderTarget2D renderTarget;

        List<Contact> contacts;
        RadarSystem radarSystem;

        Switch radarScreenSwitch;
        Switch radarEnableSwitch;

        Button launchButton;

        Knob someKnob;
        Knob rangeKnob;

        NumericDisplay distanceDisplay;
        NumericDisplay speedDisplay;

        List<Interactable> entities;

        MouseState lastMouseState;

        // te,pmteptmpe
        Texture2D shoot;
        Texture2D shootnow;

        public Tunguska()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferWidth = resw;
            graphics.PreferredBackBufferHeight = resh;
            graphics.IsFullScreen = false;
            Content.RootDirectory = "Content";
        }

        protected override void Initialize()
        {
            IsMouseVisible = true;

            renderTarget = new RenderTarget2D(graphics.GraphicsDevice, 640, 360);

            entities = new List<Interactable>();

            base.Initialize();
        }

        protected override void LoadContent()
        {
            shoot = Content.Load<Texture2D>("shoot");
            shootnow = Content.Load<Texture2D>("shoot2");

            spriteBatch = new SpriteBatch(GraphicsDevice);

            contacts = new List<Contact>();

            Aircraft targetA = new Aircraft();
            targetA.Position = new Vector3(-48, 48, 2);
            targetA.Waypoints.Add(new Vector3(-50, 50, 2));
            targetA.Waypoints.Add(new Vector3(50, 50, 1));
            targetA.Waypoints.Add(new Vector3(50, -50, 3));
            targetA.Waypoints.Add(new Vector3(-50, -50, 2));
            contacts.Add(targetA);

            Aircraft targetB = new Aircraft();
            targetB.Position = new Vector3(25, 10, 5);
            targetB.Waypoints.Add(new Vector3(30, 12, 5));
            targetB.Waypoints.Add(new Vector3(-36, 24, 4));
            contacts.Add(targetB);

            radarSystem = new RadarSystem(Content);
            radarSystem.ExteriorContacts = contacts;

            radarEnableSwitch = new Switch(Content);
            radarScreenSwitch = new Switch(Content);

            launchButton = new Button(Content);
            launchButton.OnPressed += radarSystem.Launch;

            distanceDisplay = new NumericDisplay(Content);
            speedDisplay = new NumericDisplay(Content);

            someKnob = new Knob(Content);
            someKnob.KnobTexture = Content.Load<Texture2D>("knob");
            someKnob.FrameSize = new Vector2(15, 15);
            someKnob.Size = someKnob.FrameSize;
            someKnob.FrameCount = 8;

            rangeKnob = new Knob(Content);
            rangeKnob.KnobTexture = Content.Load<Texture2D>("rangedial");
            rangeKnob.FrameSize = new Vector2(33, 32);
            rangeKnob.Size = rangeKnob.FrameSize;
            rangeKnob.FrameCount = 5;
            rangeKnob.MinimumValue = 0;
            rangeKnob.MaximumValue = 4;

            radarSystem.ScreenPosition = new Vector2(640 / 2 - 86, 360 / 2 - 86);
            distanceDisplay.ScreenPosition = new Vector2(172, 148);
            speedDisplay.ScreenPosition = new Vector2(172, 172);
            radarScreenSwitch.Position = new Vector2(200, 128);
            radarEnableSwitch.Position = new Vector2(200 + 16, 128);
            launchButton.Position = new Vector2(640 / 2 + 64, 360 / 2 + 64);
            someKnob.Position = new Vector2(420, 180);
            rangeKnob.Position = new Vector2(640 / 2 - 64 - 33, 360 / 2 + 64);

            entities.Add(radarScreenSwitch);
            entities.Add(radarEnableSwitch);
            entities.Add(launchButton);
            entities.Add(someKnob);
            entities.Add(rangeKnob);
        }

        protected override void UnloadContent()
        {
        }

        float ok;
        bool wasdownlastframe = false;
        bool wasdownagain = false;

        List<Interactable> entitiesToRelease = new List<Interactable>();
        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();


            if (!Keyboard.GetState().IsKeyDown(Keys.N))
            {
                wasdownlastframe = false;
            }
            if (Keyboard.GetState().IsKeyDown(Keys.N) && !wasdownlastframe)
            {
                wasdownlastframe = true;
                radarSystem.SelectTarget();
            }

            if (!Keyboard.GetState().IsKeyDown(Keys.L))
            {
                wasdownagain = false;
            }
            if (Keyboard.GetState().IsKeyDown(Keys.L) && !wasdownagain)
            {
                wasdownagain = true;
                radarSystem.Launch();
            }

            float deltaTime = (float)gameTime.ElapsedGameTime.TotalSeconds;


            foreach (Contact contact in contacts)
            {
                contact.Update(deltaTime);
            }
            contacts.RemoveAll(contact => contact.IsDestroyed == true);


            radarSystem.Update(deltaTime);

            radarEnableSwitch.Update(gameTime);
            radarScreenSwitch.Update(gameTime);

            radarSystem.ScreenEnabled = radarScreenSwitch.SwitchState;
            radarSystem.RadarEnabled = radarEnableSwitch.SwitchState;

            MouseState mouseState = Mouse.GetState();
            if (mouseState.LeftButton == ButtonState.Pressed && lastMouseState.LeftButton != ButtonState.Pressed)
            {
                foreach (Interactable entity in entities)
                {
                    float scaledX = mouseState.X / resfac;
                    float scaledY = mouseState.Y / resfac;

                    if (scaledX > entity.Position.X &&
                        scaledX < entity.Position.X + entity.Size.X &&
                        scaledY > entity.Position.Y &&
                        scaledY < entity.Position.Y + entity.Size.Y)
                    {
                        entity.OnClick();
                        entitiesToRelease.Add(entity);
                    }
                }
            }
            else if (mouseState.LeftButton == ButtonState.Released && lastMouseState.LeftButton != ButtonState.Released)
            {
                foreach (Interactable entity in entitiesToRelease)
                {
                    entity.OnRelease();
                }
                entitiesToRelease.Clear();
            }

            if (mouseState.ScrollWheelValue != lastMouseState.ScrollWheelValue)
            {
                foreach (Interactable entity in entities)
                {
                    float scaledX = mouseState.X / resfac;
                    float scaledY = mouseState.Y / resfac;

                    if (scaledX > entity.Position.X &&
                        scaledX < entity.Position.X + entity.Size.X &&
                        scaledY > entity.Position.Y &&
                        scaledY < entity.Position.Y + entity.Size.Y)
                    {
                        bool direction = mouseState.ScrollWheelValue > lastMouseState.ScrollWheelValue;
                        entity.OnScroll(direction);
                    }
                }
            }

            lastMouseState = mouseState;


            speedDisplay.NumberToDisplay++;
            distanceDisplay.NumberToDisplay = (int)gameTime.TotalGameTime.TotalSeconds;


            base.Update(gameTime);
        }

        float timer;
        bool ovd;

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(new Color(0.05f, 0.05f, 0.05f));

            GraphicsDevice.SetRenderTarget(renderTarget);
            GraphicsDevice.Clear(new Color(0.05f, 0.05f, 0.05f));
            spriteBatch.Begin(SpriteSortMode.Deferred, null, SamplerState.PointClamp);

            radarSystem.Draw(spriteBatch);

            radarEnableSwitch.Draw(spriteBatch);
            radarScreenSwitch.Draw(spriteBatch);
            launchButton.Draw(spriteBatch);
            distanceDisplay.Draw(spriteBatch);
            speedDisplay.Draw(spriteBatch);
            someKnob.Draw(spriteBatch);
            rangeKnob.Draw(spriteBatch);

            if (radarSystem.FLASH)
            {
                timer += (float)gameTime.ElapsedGameTime.TotalSeconds;
                if (timer < 1.0f)
                {
                    ovd = true;
                }
                if (timer > 1.0f)
                {
                    ovd = false;
                }
                if (timer >= 2.0f)
                {
                    timer = 0.0f;
                }
            }
            else
                ovd = false;

            if (!radarSystem.TEMPHASLOCK || ovd)
            {
                spriteBatch.Draw(shoot, new Vector2(640 / 2 - 37 / 2, 270), Color.White);
            }
            else if (radarSystem.TEMPHASLOCK)
            {
                spriteBatch.Draw(shootnow, new Vector2(640 / 2 - 37 / 2, 270), Color.White);
            }

            spriteBatch.End();
            GraphicsDevice.SetRenderTarget(null);

            spriteBatch.Begin(SpriteSortMode.Immediate, null, SamplerState.PointClamp);
            spriteBatch.Draw(renderTarget, new Rectangle(0, 0, resw, resh), Color.White);
            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
