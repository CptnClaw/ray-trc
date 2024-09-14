# ray-trc
Ray tracer built over several weekends.

### Features
- Sphere primitives.
- Three material types:
    - Diffuse (Lambertian).
    - Metal (Reflectance with configurable fuzziness).
    - Glass (Dielectric).
- Acceleration using bounding volume hierarchy (BVH).
    - Axis-aligned bounding boxes.
    - Surface area heuristics (SAH).
    - Tiled ray ordering.
- Gaussian subpixel sampling.
- Depth of field blur.
- Rotation animations.

### Current progress
![Progress thus far](https://raw.githubusercontent.com/CptnClaw/ray-trc/master/orot.png)
![Book 1 final](https://raw.githubusercontent.com/CptnClaw/ray-trc/master/final-dof0.png)

### Acknowledgements
This is a learning project for me to experiment with ray tracing and rendering techniques. 
Big thanks to Peter Shirley's [Ray Tracing in One Weekend Book Series](https://raytracing.github.io/)
for providing a wonderful and free online resource on the subject.