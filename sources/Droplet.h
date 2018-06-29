#ifndef DROPLET_H
#define DROPLET_H

#include <iostream>
#include "Direction.h"
#include "Dispenser.h"
#include "DropletData.h"

typedef unsigned long long ULL;

class Droplet {
private:
    int identifier;
    int type;
    Point position;

    bool dispensed;

    bool mixing;
    int remainingMixingTime;    

    bool detecting;
    int remainingDetectingTime;

    void setData(const DropletData& dropletData);

    Droplet& operator = (const Droplet& droplet);
public:
    Droplet(const DropletData& dropletData);
    Droplet(const Droplet* precursor, const Direction& direction);
    Droplet(const Droplet* droplet1, const Droplet* droplet2);


    ULL hash() const;

    bool underMixing() const;

    void startDetection();
    bool underDetection() const;
    bool detected() const;

    int getIdentifier() const;
    int getType() const;
    Point getPosition() const;

    int estimatedTime() const;
    
    friend std::ostream& operator << (std::ostream&, const Droplet&);
};

#endif  //DROPLET_H