using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;

namespace Tunguska
{
    class Aircraft : Contact
    {
        public float TopSpeed;

        public List<Vector3> Waypoints;
        public int CurrentWaypoint;

        Vector3 lastDirection;

        public Aircraft()
        {
            TopSpeed = 3.0f;

            Waypoints = new List<Vector3>();
            CurrentWaypoint = 0;

            lastDirection = new Vector3(1.0f, 0.0f, 0.0f);
        }

        public override void Update(float deltaTime)
        {
            if (Waypoints.Count <= CurrentWaypoint)
                CurrentWaypoint = 0;

            if (Waypoints.Count < CurrentWaypoint)
                Position += lastDirection * TopSpeed * deltaTime;

            Vector3 waypoint = Waypoints[CurrentWaypoint];
            Vector3 direction = waypoint - Position;
            direction.Normalize();

            lastDirection = direction;

            Position += direction * TopSpeed * deltaTime;

            if (Vector3.Distance(Position, waypoint) < 1.0f)
                CurrentWaypoint++;
        }
    }
}
