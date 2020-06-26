using Microsoft.Xna.Framework;

namespace Tunguska
{
    class RadarContact
    {
        public Vector3 LastKnownPosition;
        public Vector3 LastKnownVelocity;

        public float TimeSinceLastDetection;
    }
}
