class Point {
private:

	double x;
	double y;
	
public:
	void Show() {

		x = 0.0;
		y = 0.0;

	}
 };
2) 
class Rectangle {

private:
	double width;
	double height;
	 
public:

	Rectangle(double w, double h) {

		width = w;
		height = h;
    }

	void Area() {
		std::cout << "s=" << width * height <<std:: endl;

	}
	void Perimeter() {

		std::cout<<"P="<<2 * (width + height)<<std::endl;

	}

};
int main() {

	Rectangle R1(3.4, 5.6);
	R1.Area();
	R1.Perimeter();

	return 0;
}
