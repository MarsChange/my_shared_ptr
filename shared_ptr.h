#include<iostream>
using namespace std;

namespace my_shared_ptr {
	template<class T>
	class shared_ptr {
	public:
		//默认空构造，初始化时引用计为0
		shared_ptr() : _ptr(NULL), _reference_count(NULL) {}
		//构造函数
		shared_ptr(T* t) {
			_ptr = t;
			_reference_count = new int(1);
		}
		//引用
		shared_ptr(const shared_ptr<T>& s) {
			_ptr = s._ptr;
			_reference_count = s._reference_count;
			++(*_reference_count);
		}
		//重载运算符->
		T* operator->() {
			return _ptr;
		}
		//重载运算符*
		T& operator*() {
			return *_ptr;
		}
		//重载赋值运算符=
		shared_ptr<T>& operator=(const shared_ptr<T>& s) {
			_ptr = s._ptr;
			_reference_count = s._reference_count;
			++(*_reference_count);
			return *this;
		}
		//获取原指针
		T* get() {
			return _ptr;
		}
		//获取引用计数
		int use_count() {
			if (_reference_count) return *_reference_count;
		}
		//重置
		void reset() {
			if (_ptr && --(*_reference_count) == 0) {
				delete _ptr;
			}
		}
		//析构函数
		~shared_ptr() {
			if (_ptr && --(*_reference_count) == 0) {
				delete _ptr;
				delete _reference_count;
			}
		}
	private:
		T* _ptr;
		int* _reference_count;
	};
};
