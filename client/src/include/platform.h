#ifndef __PLATFORM_H
#define __PLATFORM_H

class Platform : public Object
{
    static Platform* first_platform;
    static Platform* last_platform;
    Platform* next_platform;
    Platform* prev_platform;

    public:
    double dy;
    double gpos;
    double y_rotation; /* remember for physics */
    union
    {
        double radius;
        struct
        {
            /* 2 Gründe/Vorraussetzungen für diese Entscheidung hier extend_N zu speichern:
               a) pro Platform und nicht pro Mesh, weil die Matrix des Objekts dieser Instanz (Platform) eventuell gestretched sein könnte
               b) extend und nicht min/max, weil wir davon ausgehen, dass der Mittelpunkt des Objekts immer der Ursprung des Objekt-Koordinatensystems ist
               */
            double extend_x;
            double extend_z;
        };
    };

    bool is_circular;

    static Platform* FirstPlatform()   { return first_platform; };
    static Platform* LastPlatform()    { return last_platform;  };
    Platform* PrevPlatform()           { return prev_platform;  };
    Platform* NextPlatform()           { return next_platform;  };

    Platform(bool _is_circular, Mesh* m, Texture* t, double x, double y, double z);
    ~Platform();
    void RotateY(double angle); /* only rotation around y axis is allowed for platforms */
    void Anim();
    bool Collision();
    void Land();
};


#endif // __PLATFORM_H
