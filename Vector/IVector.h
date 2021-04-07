using ValueType = double;

class IVector
{
public:
	virtual void pushBack(const ValueType& value) = 0;
	virtual void pushFront(const ValueType& value) = 0;
	virtual void insert(const ValueType& value, size_t idx) = 0;
	
	virtual ValueType& at(size_t idx) = 0;
	virtual const ValueType& at(size_t idx) const = 0;
	
	virtual void clear() = 0;
	
	virtual ~IVector() = default;
};
