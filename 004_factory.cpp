#include <iostream>
#include <memory>

class IWarehouseTransport {

	public:
		virtual ~IWarehouseTransport() {}
		virtual void pickup_package() = 0;
		virtual void transport_package() = 0;
		virtual void leave_package() = 0;

};

enum ObjectType {CAR, BOAT, PLANE};

class Car : public IWarehouseTransport {
	public:
		Car() {std::cout << "\nCar is produced...";};
		void pickup_package() override {
			std::cout << "Car Picking package..." << std::endl;
		}

		void transport_package() override {
			std::cout << "Car Transporting package..." << std::endl;
		}

		void leave_package() override {
			std::cout << "Car Leaving a package..." << std::endl;
		}
};

class Boat : public IWarehouseTransport {
	public:
		Boat() {std::cout << "\nBoat is produced...";};
		void pickup_package() override {
			std::cout << "Boat Picking package..." << std::endl;
		}

		void transport_package() override {
			std::cout << "Boat Transporting package..." << std::endl;
		}

		void leave_package() override {
			std::cout << "Boat Leaving a package..." << std::endl;
		}
};

class Plane : public IWarehouseTransport {
	public:
		Plane() { std::cout << "\nPlane is produced..." << std::endl;}
		void pickup_package() override {
			std::cout << "Plane Picking package..." << std::endl;
		}

		void transport_package() override {
			std::cout << "Plane Transporting package..." << std::endl;
		}

		void leave_package() override {
			std::cout << "Plane Leaving a package..." << std::endl;
		};

};

std::unique_ptr<IWarehouseTransport> make_transport_object_factory(ObjectType type) {
	if (type == ObjectType::CAR){
		return std::make_unique<Car>(); // Car* c = new Car();
	}
	else if (type == ObjectType::BOAT) {
		return std::make_unique<Boat>();
	}
	else if (type == ObjectType::PLANE) {
		return std::make_unique<Plane>();
	}
	return nullptr;
}


int main() {
	
	auto myTransport1 = make_transport_object_factory(ObjectType::CAR);
	auto myTransport2 = make_transport_object_factory(ObjectType::BOAT);
	auto myTransport3 = make_transport_object_factory(ObjectType::PLANE);
	myTransport1->pickup_package();
	myTransport1->transport_package();
	myTransport1->leave_package();
	myTransport2->pickup_package();
	myTransport2->transport_package();
	myTransport2->leave_package();
	myTransport3->pickup_package();
	myTransport3->transport_package();
	myTransport3->leave_package();

	//delete myTransport1
	//delete myTransport2
	//delete myTransport3
	//We can use shared_ptr or unique_ptr to make the memory safier and our API better

	return 0;
}
