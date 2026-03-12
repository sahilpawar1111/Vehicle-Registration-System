#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    int id;
    string maker;
    string model;
    int year;

public:
    static int total;

    Vehicle() : id(0), maker(""), model(""), year(0) { total++; }

    Vehicle(int vid, string mk, string md, int yr)
        : id(vid), maker(mk), model(md), year(yr)
    {
        total++;
    }

    virtual ~Vehicle() { total--; }

    int getID() { return id; }

    virtual void display()
    {
        cout << "Vehicle ID: " << id << endl;
        cout << "Manufacturer: " << maker << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
};

int Vehicle::total = 0;



class Car : public Vehicle
{
protected:
    string fuel;

public:
    Car() : fuel("") {}

    Car(int id, string mfg, string mdl, int yr, string f)
        : Vehicle(id, mfg, mdl, yr), fuel(f) {}

    void display()
    {
        Vehicle::display();
        cout << "Fuel: " << fuel << endl;
    }
};



class ElectricCar : public Car
{
protected:
    int battery;

public:
    ElectricCar() : battery(0) {}

    ElectricCar(int id, string mfg, string mdl, int yr, string f, int bat)
        : Car(id, mfg, mdl, yr, f), battery(bat) {}

    void display()
    {
        Car::display();
        cout << "Battery: " << battery << " kWh" << endl;
    }
};



class Aircraft
{
protected:
    int range;

public:
    Aircraft() : range(0) {}
    Aircraft(int r) : range(r) {}
};


class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar() {}

    FlyingCar(int id, string mfg, string mdl, int yr, string f, int r)
        : Car(id, mfg, mdl, yr, f), Aircraft(r) {}

    void display()
    {
        Car::display();
        cout << "Flight Range: " << range << endl;
    }
};


class SportsCar : public ElectricCar
{
    int topSpeed;

public:
    SportsCar() : topSpeed(0) {}

    SportsCar(int id, string mfg, string mdl, int yr, string f, int bat, int sp)
        : ElectricCar(id, mfg, mdl, yr, f, bat), topSpeed(sp) {}

    void display()
    {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << endl;
    }
};



class Sedan : public Car
{
public:
    Sedan() {}
    Sedan(int id, string m, string md, int yr, string f)
        : Car(id, m, md, yr, f) {}
};



class SUV : public Car
{
public:
    SUV() {}
    SUV(int id, string m, string md, int yr, string f)
        : Car(id, m, md, yr, f) {}
};



class VehicleRegistry
{
    Vehicle *list[100];
    int count;

public:
    VehicleRegistry() : count(0) {}

    void add(Vehicle *v)
    {
        if (count < 100)
        {
            list[count++] = v;
            cout << "\nVehicle added!\n";
        }
    }

    void showAll()
    {
        if (count == 0)
        {
            cout << "\nNo vehicles.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            list[i]->display();
            cout << endl;
        }
    }

    void search(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (list[i]->getID() == id)
            {
                list[i]->display();
                cout << endl;
                return;
            }
        }
        cout << "Vehicle not found!\n";
    }
};


int main()
{
    VehicleRegistry reg;
    int ch;

    do
    {
        cout << "\n--- Vehicle Registry Menu ---\n";
        cout << "1. Add Vehicle\n";
        cout << "2. View All\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1)
        {
            int type;
            cout << "1.Car  2.ElectricCar  3.FlyingCar  4.SportsCar  5.Sedan  6.SUV\n";
            cin >> type;

            int id, yr, bat, rng, sp;
            string mfg, mdl, fuel;

            cout << "ID: ";
            cin >> id;
            cout << "Manufacturer: ";
            cin >> mfg;
            cout << "Model: ";
            cin >> mdl;
            cout << "Year: ";
            cin >> yr;

            if (type == 1)
            {
                cout << "Fuel: ";
                cin >> fuel;
                reg.add(new Car(id, mfg, mdl, yr, fuel));
            }
            else if (type == 2)
            {
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> bat;
                reg.add(new ElectricCar(id, mfg, mdl, yr, fuel, bat));
            }
            else if (type == 3)
            {
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Range: ";
                cin >> rng;
                reg.add(new FlyingCar(id, mfg, mdl, yr, fuel, rng));
            }
            else if (type == 4)
            {
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> bat;
                cout << "Top Speed: ";
                cin >> sp;
                reg.add(new SportsCar(id, mfg, mdl, yr, fuel, bat, sp));
            }
            else if (type == 5)
            {
                cout << "Fuel: ";
                cin >> fuel;
                reg.add(new Sedan(id, mfg, mdl, yr, fuel));
            }
            else if (type == 6)
            {
                cout << "Fuel: ";
                cin >> fuel;
                reg.add(new SUV(id, mfg, mdl, yr, fuel));
            }
        }
        else if (ch == 2)
        {
            reg.showAll();
        }
        else if (ch == 3)
        {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            reg.search(id);
        }

    } while (ch != 4);

    return 0;
}
