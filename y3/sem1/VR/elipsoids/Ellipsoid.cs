using System;


namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }
        
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // TODO: ADD CODE HERE
            // a * (t^2) + b * t + c = 0
            
            // a = (dx.x^2 * B^2 * C^2) + (dx.y^2 * A^2 * C^2) + (dx.z^2 * A^2 * B^2)
            var a = (line.Dx.X * line.Dx.X) * (SemiAxesLength.Y * SemiAxesLength.Y) * (SemiAxesLength.Z * SemiAxesLength.Z);
            a += (line.Dx.Y * line.Dx.Y) * (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Z * SemiAxesLength.Z);
            a += (line.Dx.Z * line.Dx.Z) * (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Y * SemiAxesLength.Y);

            // b = 2 * ((dx.x * (x0.x - xc) * B^2 * C^2) + (dx.y * (x0.y - yc) * A^2 * C^2) + (dx.z * (x0.z - zc) * A^2 * B^2))
            var b = line.Dx.X * (line.X0.X - Center.X) * (SemiAxesLength.Y * SemiAxesLength.Y) * (SemiAxesLength.Z * SemiAxesLength.Z);
            b += line.Dx.Y * (line.X0.Y - Center.Y) * (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Z * SemiAxesLength.Z);
            b += line.Dx.Z * (line.X0.Z - Center.Z) * (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Y * SemiAxesLength.Y);
            b *= 2.0;

            // c = ((x0.x - xc)^2 * B^2 * C^2) + ((x0.y - yc)^2 * A^2 * C^2) + ((x0.z - zc)^2 * A^2 * B^2) - (A^2 * B^2 + C^2)
            var c = (line.X0.X - Center.X) * (line.X0.X - Center.X) * (SemiAxesLength.Y * SemiAxesLength.Y) * (SemiAxesLength.Z * SemiAxesLength.Z);
            c += (line.X0.Y - Center.Y) * (line.X0.Y - Center.Y) * (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Z * SemiAxesLength.Z);
            c += (line.X0.Z - Center.Z) * (line.X0.Z - Center.Z) * (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Y * SemiAxesLength.Y);
            c -= (SemiAxesLength.X * SemiAxesLength.X) * (SemiAxesLength.Y * SemiAxesLength.Y) * (SemiAxesLength.Z * SemiAxesLength.Z) * (Radius * Radius);

            var delta = b * b - 4.0 * a * c;
            if (delta < 0.001)
            {
                return new Intersection();
            }
            var t1 = (-b + Math.Sqrt(delta)) / (2.0 * a);
            var t2 = (-b - Math.Sqrt(delta)) / (2.0 * a);

            if ((minDist <= t1 && t1 <= maxDist) && !(minDist <= t2 && t2 <= maxDist))
            {
                var norm_v1 = line.CoordinateToPosition(t1) - Center;
                var norm_x1 = 2.0 * norm_v1.X / (SemiAxesLength.X * SemiAxesLength.X);
                var norm_y1 = 2.0 * norm_v1.Y / (SemiAxesLength.Y * SemiAxesLength.Y);
                var norm_z1 = 2.0 * norm_v1.Z / (SemiAxesLength.Z * SemiAxesLength.Z);
                var normalized1 = new Vector(norm_x1, norm_y1, norm_z1);
                normalized1 = normalized1.Normalize();
                return new Intersection(true, true, this, line, t1, normalized1);
            }
            if (!(minDist <= t1 && t1 <= maxDist) && (minDist <= t2 && t2 <= maxDist))
            {
                var norm_v2 = line.CoordinateToPosition(t2) - Center;
                var norm_x2 = 2.0 * norm_v2.X / (SemiAxesLength.X * SemiAxesLength.X);
                var norm_y2 = 2.0 * norm_v2.Y / (SemiAxesLength.Y * SemiAxesLength.Y);
                var norm_z2 = 2.0 * norm_v2.Z / (SemiAxesLength.Z * SemiAxesLength.Z);
                var normalized2 = new Vector(norm_x2, norm_y2, norm_z2);
                normalized2 = normalized2.Normalize();
                return new Intersection(true, true, this, line, t2, normalized2);
            }

            // if both of them are between minDist and maxDist check which one is closer
            if (t1 < t2)
            {
                var norm_v3 = line.CoordinateToPosition(t1) - Center;
                var norm_x3 = 2.0 * norm_v3.X / (SemiAxesLength.X * SemiAxesLength.X);
                var norm_y3 = 2.0 * norm_v3.Y / (SemiAxesLength.Y * SemiAxesLength.Y);
                var norm_z3 = 2.0 * norm_v3.Z / (SemiAxesLength.Z * SemiAxesLength.Z);
                var normalized3 = new Vector(norm_x3, norm_y3, norm_z3);
                normalized3 = normalized3.Normalize();
                return new Intersection(true, true, this, line, t1, normalized3);
            }
            var norm_v4 = line.CoordinateToPosition(t2) - Center;
            var norm_x4 = 2.0 * norm_v4.X / (SemiAxesLength.X * SemiAxesLength.X);
            var norm_y4 = 2.0 * norm_v4.Y / (SemiAxesLength.Y * SemiAxesLength.Y);
            var norm_z4 = 2.0 * norm_v4.Z / (SemiAxesLength.Z * SemiAxesLength.Z);
            var normalized4 = new Vector(norm_x4, norm_y4, norm_z4);
            normalized4 = normalized4.Normalize();
            return new Intersection(true, true, this, line, t2, normalized4);
        }
    }
}
