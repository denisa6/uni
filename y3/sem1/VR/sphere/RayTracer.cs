using System;
using System.Runtime.InteropServices;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            var u = n * viewPlaneSize / imgSize;
            u -= viewPlaneSize / 2;
            return u;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = new Intersection();

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }

        private bool IsLit(Vector point, Light light)
        {
            // ADD CODE HERE: Detect whether the given point has a clear line of sight to the given light
            var line = new Line(light.Position, point);
            var intersection = FindFirstIntersection(line, 0, 100000);
            if (!intersection.Valid || !intersection.Visible)
                return true;
            return intersection.T > (light.Position - point).Length() - 0.001;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color();
            //var viewParallel = (camera.Up ^ camera.Direction).Normalize();
            var viewParallel = camera.Up ^ camera.Direction;
            var image = new Image(width, height);

            var vecW = camera.Direction * camera.ViewPlaneDistance;
            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    // ADD CODE HERE: Implement pixel color calculation
                    var x1 = camera.Position + camera.Direction * camera.ViewPlaneDistance + camera.Up * ImageToViewPlane(j, height, camera.ViewPlaneHeight) + viewParallel * ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    var x0 = camera.Position;
                    var ray = new Line(x0, x1);
                    var intersection = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);
                    if (intersection.Valid && intersection.Visible)
                    {
                        var color = new Color();
                        for (var k = 0; k < lights.Length; k++)
                        {
                            var color2 = new Color();
                            color2 = intersection.Geometry.Material.Ambient * lights[k].Ambient;
                            if (IsLit(intersection.Position, lights[k]))
                            {
                                var v = intersection.Position;
                                var e = (camera.Position - v).Normalize();
                                var n = ((Sphere)intersection.Geometry).Normal(v);
                                var t = (lights[k].Position - v).Normalize();
                                var r = (n * (n * t) * 2 - t).Normalize();

                                if (n * t > 0)
                                {
                                    color += intersection.Geometry.Material.Diffuse * lights[k].Diffuse * (n * t);
                                }
                                if (e * r > 0)
                                {
                                    color += intersection.Geometry.Material.Specular * lights[k].Specular * Math.Pow(e * r, intersection.Geometry.Material.Shininess);
                                }
                                color *= lights[k].Intensity;
                            }
                            color += color2;
                        }
                        image.SetPixel(i, j, color);
                    }
                    else 
                    {
                        image.SetPixel(i, j, background);
                    };
                }
            }

            image.Store(filename);
        }
    }
}