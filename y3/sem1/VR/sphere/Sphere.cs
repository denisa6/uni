using System;

namespace rt
{
    public class Sphere : Geometry
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // ADD CODE HERE: Calculate the intersection between the given line and this sphere
            // (dx * t + x0 - c)^2 = R^2 => dx^2 * t^2 + 2 * dx * t * (x0 - c) + (x0 - c)^2 - R^2 = 0
            // (dx^2) * (t^2) + (2 * (dx * x0 - dx * c)) + ((x0 - c)^2 - R^2) = 0
            // a * (t^2) + b * t + c = 0
            var a = line.Dx * line.Dx;
            var b = 2.0 * ((line.Dx * line.X0) - (line.Dx * Center));
            var c = (line.X0 - Center) * (line.X0 - Center) - (Radius * Radius);
            var delta = (b * b) - 4.0 * a * c;

            // the line doesn't intersects the sphere
            if (delta < 0.0)
            {
                return new Intersection();
            }

            // the line intersects the sphere
            var t1 = (-b + Math.Sqrt(delta)) / 2.0 * a;
            var t2 = (-b - Math.Sqrt(delta)) / 2.0 * a;

            // check whether t1 and t2 are between the limits
            if((minDist <= t1 && t1 <= maxDist) && !(minDist <= t2 && t2 <= maxDist)){
                return new Intersection(true, true, this, line, t1);
            }
            if (!(minDist <= t1 && t1 <= maxDist) && (minDist <= t2 && t2 <= maxDist))
            {
                return new Intersection(true, true, this, line, t2);
            }
            if (!(minDist <= t1 && t1 <= maxDist) && !(minDist <= t2 && t2 <= maxDist))
            {
                var intersection = new Intersection();
                intersection.Visible = false;
                return intersection;
            }

            // if both of them are between minDist and maxDist check which one is closer
            if(t1 < t2){
                return new Intersection(true, true, this, line, t1);
            }
            return new Intersection(true, true, this, line, t2);

        }

        public override Vector Normal(Vector v)
        {
            var n = v - Center;
            n.Normalize();
            return n;
        }
    }
}