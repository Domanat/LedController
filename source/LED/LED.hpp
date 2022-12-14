#include <mutex>

enum Color { red = 0, green, blue };
enum Status {OK = 0, FAILED = 0};

class LED
{
public:

	bool GetState() 
	{
		std::lock_guard<std::mutex> lock(mutex);
		return isOn;
	}

	void SetState(bool value)
	{
		std::lock_guard<std::mutex> lock(mutex);
		isOn = value;
	}

	Color GetColor() 
	{
		std::lock_guard<std::mutex> lock(mutex);
		return color;
	}

	void SetColor(Color newColor)
	{
		std::lock_guard<std::mutex> lock(mutex);
		color = newColor;
	}

	double GetRate() 
	{
		std::lock_guard<std::mutex> lock(mutex);
		return rate;
	}

	void SetRate(double newRate)
	{
		std::lock_guard<std::mutex> lock(mutex);
		rate = newRate;
	}

private:

	std::mutex mutex;

	bool isOn = false;
	Color color;
	double rate;
};