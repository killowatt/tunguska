using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Tunguska
{
    class RadarSystem
    {
        public bool TEMPHASLOCK;
        public bool FLASH;

        public Vector2 ScreenPosition;
        public Vector3 WorldPosition;

        public float CurrentRange;

        public bool ScreenEnabled;
        public bool RadarEnabled;

        private float lastRadarRotation;
        private float radarRotation;

        public List<Contact> ExteriorContacts;
        private Dictionary<Contact, RadarContact> contacts;

        int lastind;
        private Contact selectedContact;
        private Missile Missile;

        Texture2D screenTexture;
        Texture2D coverTexture;
        Texture2D lineTexture;
        Texture2D contactTexture;
        Texture2D selectedTexture;

        public void SelectTarget()
        {
            if (contacts.Count() <= 0)
                return;

            lastind++;

            if (contacts.Count() <= lastind)
                lastind = 0;

            selectedContact = contacts.Keys.ElementAt(lastind);
            if (selectedContact == Missile)
                selectedContact = null;
        }

        public void Launch()
        {
            if (Missile != null || selectedContact == null)
                return;

            Missile = new Missile();
            Missile.Target = selectedContact;

            ExteriorContacts.Add(Missile);
        }

        public RadarSystem(ContentManager content)
        {
            CurrentRange = 172.0f / 2.0f;

            ScreenEnabled = false;
            RadarEnabled = false;

            contacts = new Dictionary<Contact, RadarContact>();

            screenTexture = content.Load<Texture2D>("radarscreen");
            coverTexture = content.Load<Texture2D>("radarcover");
            lineTexture = content.Load<Texture2D>("radar");
            contactTexture = content.Load<Texture2D>("contact");
            selectedTexture = content.Load<Texture2D>("contactselected");
        }

        public void Update(float deltaTime)
        {
            if (selectedContact != null)
                TEMPHASLOCK = true;
            else
                TEMPHASLOCK = false;

            if (selectedContact != null && Vector3.Distance(WorldPosition, selectedContact.Position) < 20.0f)
                FLASH = true;
            else
                FLASH = false;



            if (Missile != null && Missile.IsDestroyed)
                Missile = null;

            if (Missile != null && Missile.Target != selectedContact)
                Missile.Target = selectedContact;



            if (RadarEnabled)
                radarRotation += MathHelper.TwoPi / 90.0f;

            if (radarRotation > MathHelper.TwoPi)
            {
                lastRadarRotation = radarRotation - lastRadarRotation;
                radarRotation = 0.0f;
            }

            foreach (Contact contact in ExteriorContacts)
            {
                if (Vector3.Distance(WorldPosition, contact.Position) > CurrentRange)
                    continue;

                Vector3 position = contact.Position;
                Vector2 direction = new Vector2(position.X, position.Y);
                direction.Normalize();

                float angle = (float)Math.Acos(Vector2.Dot(direction, Vector2.UnitX));
                if (direction.Y < 0.0f)
                    angle = MathHelper.TwoPi - angle;

                if (angle <= radarRotation &&
                    angle >= lastRadarRotation)
                {
                    if (!contacts.ContainsKey(contact))
                        contacts[contact] = new RadarContact();

                    RadarContact radarContact = contacts[contact];

                    radarContact.LastKnownPosition = position;
                    radarContact.TimeSinceLastDetection = 0.0f;
                }
            }

            List<Contact> lostContacts = new List<Contact>();
            foreach (KeyValuePair<Contact, RadarContact> contact in contacts)
            {
                contact.Value.TimeSinceLastDetection += deltaTime;
                if (contact.Value.TimeSinceLastDetection >= 2.0f)
                    lostContacts.Add(contact.Key);
            }
            foreach (Contact contact in lostContacts)
            {
                if (selectedContact == contact)
                    selectedContact = null;
                contacts.Remove(contact);
            }

            lastRadarRotation = radarRotation;
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(screenTexture, ScreenPosition, Color.White);

            if (ScreenEnabled)
            {
                // Draw contacts
                foreach (KeyValuePair<Contact, RadarContact> contact in contacts)
                {
                    Texture2D texture = contactTexture;
                    if (contact.Key == selectedContact)
                        texture = selectedTexture;

                    Vector2 position = new Vector2(
                        contact.Value.LastKnownPosition.X,
                        contact.Value.LastKnownPosition.Y);

                    position += ScreenPosition + new Vector2(172 / 2);

                    float alpha = (2.0f - contact.Value.TimeSinceLastDetection) / 2.0f;
                    Color color = Color.FromNonPremultiplied(255, 255, 255, (int)(alpha * 255));
                    spriteBatch.Draw(texture, position, color);
                }

                // Draw radar line
                Vector2 LinePosition = ScreenPosition + new Vector2(86.0f);
                spriteBatch.Draw(lineTexture, LinePosition, null, Color.White,
                    radarRotation, new Vector2(172, 172), 0.5f, SpriteEffects.None, 0.0f);
            }

            spriteBatch.Draw(coverTexture, ScreenPosition, Color.White);
        }
    }
}
