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
            Vector norm = new Vector();
            bool valid = false, visibile = false;
            double t = -1;
            Color color = new Color();


            if ((minDist <= t1 && t1 <= maxDist) && !(minDist <= t2 && t2 <= maxDist))
            {
                valid = true;
                visibile = true;
                t = t1;
            }
            else if (!(minDist <= t1 && t1 <= maxDist) && (minDist <= t2 && t2 <= maxDist))
            {
                valid = true;
                visibile = true;
                t = t2;
            }
            // if both of them are between minDist and maxDist check which one is closer
            else if (t1 < t2)
            {
                valid = true;
                visibile = true;
                t = t1;
            }
            else
            {
                valid = true;
                visibile = true;
                t = t2;
            }

            norm = line.CoordinateToPosition(t) - Center;
            var norm_x = 2.0 * norm.X / (SemiAxesLength.X * SemiAxesLength.X);
            var norm_y = 2.0 * norm.Y / (SemiAxesLength.Y * SemiAxesLength.Y);
            var norm_z = 2.0 * norm.Z / (SemiAxesLength.Z * SemiAxesLength.Z);
            norm = new Vector(norm_x, norm_y, norm_z);
            norm = norm.Normalize();
            return new Intersection(valid, visibile, this, line, t, norm, this.Material, color);
        }
    }
}
