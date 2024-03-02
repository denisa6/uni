
using System;

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
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = Intersection.NONE;

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

        private bool IsLit(Vector point, Light light, Camera camera)
        {
            var line = new Line(light.Position, point);
            var intersection = FindFirstIntersection(line, camera.BackPlaneDistance, camera.FrontPlaneDistance);
            if (!intersection.Valid || !intersection.Visible)
                return true;
            return intersection.T > (light.Position - point).Length() - 0.001;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(0.2, 0.2, 0.2, 1.0);
            var image = new Image(width, height);
            var viewParallel = camera.Up ^ camera.Direction;

            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    var x1 = camera.Position + camera.Direction * camera.ViewPlaneDistance + camera.Up * ImageToViewPlane(j, height, camera.ViewPlaneHeight) + viewParallel * ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    var x0 = camera.Position;
                    var ray = new Line(x0, x1);
                    var intersection = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                    var color = new Color(0, 0, 0, 1);
                    if (intersection.Valid && intersection.Visible)
                    {
                        var material = intersection.Material;
                        foreach (var light in lights)
                        {
                            var lightColor = material.Ambient * light.Ambient;
                            if (IsLit(intersection.Position, light, camera))
                            {
                                var v = intersection.Position;
                                var e = (camera.Position - v).Normalize();
                                var n = intersection.Normal;
                                var t = (light.Position - v).Normalize();
                                var r = (n * (n * t) * 2 - t);

                                if (n * t > 0)
                                {
                                    lightColor += material.Diffuse * light.Diffuse * (n * t);
                                }
                                if (e * r > 0)
                                {
                                    lightColor += material.Specular * light.Specular * Math.Pow(e * r, material.Shininess);
                                }
                                lightColor *= light.Intensity;
                            }
                            color += lightColor;
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