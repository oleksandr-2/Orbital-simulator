#include <cmath>
#include <iostream>
#include <string>
#include <GL/glut.h>

const double G = 6.67430e-11;

//mathematical operations with vectors such as addition, subtraction and scaling.
class Vector{
    public:
        double x, y ,z;
        Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        Vector operator+(const Vector& other) const
        {
            return Vector(x + other.x, y + other.y, z + other.z);
        }

        Vector operator-(const Vector& other) const
        {
            return Vector(x - other.x, y - other.y, z -other.z);
        }

        Vector operator*(double scalar) const
        {
            return Vector(x * scalar, y * scalar, z * scalar);
        }

        double magnitude() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector normalize() const
        {
            double mag = magnitude();
            return *this * (1 / mag);
        }
};

//This class is used to represent celestial bodies with their physical properties.
class CelestialBody
{
    public:
        Vector position;
        Vector velocity;
        double mass;
        double radius;
        std:: string name;

        CelestialBody(std:: string name, Vector position, Vector velocity, double mass, double radius)
            : position(position), velocity(velocity), mass(mass), radius(radius) {}

        void updatePosition(double dt)
        {
            position = position + velocity * dt;
        }

        void printInfo() const
        {
            std:: cout << "Name: " << name << "\n"
                       << "Mass: " << mass << " kg\n"
                       << "Radius: " << radius << " meters\n"
                       << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n"
                       << "Velocity: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")\n" 
        }
};

//The Universe class manages all celestial bodies and their interactions.
class Universe
{
    private :
        std :: vector<CelestialBody> bodies;

    public:
        void addBody(CelestialBody body)
        {
            bodies.push_back(body);
        }

        void simulate(double dt)
        {
            std:: vector<Vector> forces(bodies.size(), Vector(0, 0, 0));
            for (size_t i = 0; i < bodies.size(); ++i)
                {
                    for (size_t j = i + 1; j < bodies.size(); ++j)
                    {
                        Vector direction = bodies[j].position - bodies[i].position;
                        double distance = direction.magnitude();
                        double forceMagnitude = (G * bodies[i].mass * bodies[j].mass) / (distance * distance);
                        Vector force = direction.normalize() * forceMagnitude;

                        force[i] = force[i] + force;
                        force[j] = force[j] - force;
                    }
                }
            
            for (size_t i = 0; i < bodies.size(); ++i)
            {
                bodies[i].velocity = bodies[i].velocity + (forces[i] / bodies[i].mass) * dt;
                bodies[i].updatePosition(dt);
            }
        }

        void printUniverse()
        {
            for (const auto& body : bodies)
            {
                body.printInfo();
                std:: cout << std:: end1;
            }
        }
};

void renderScene()
{
    glClear(GL_COLOR_BUFFRE_BIT | GL_DEPTH_BUFFER_BIR);

    // Here will be the code for rendering objects
    //  can use glTranslatef, glRotatef to place objects in space
    // glScalef can be used to scale objects
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Orbital Simulator with OpenGL");

    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 0;
}
   

