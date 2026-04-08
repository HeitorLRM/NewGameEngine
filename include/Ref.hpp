#pragma once

#include "Resource.hpp"

#include <ostream>
#include <type_traits>

namespace engine {

class RefCtrl;

template<typename T>
class Ref {
public:
	Ref() = default;
	explicit Ref(T* resource);
	Ref(const Ref& other);
	~Ref();

	template<typename U> Ref(
		const Ref<U>& other, 
		std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0
	);

	template<typename U>
	Ref<U> d_cast();


	int ref_count();
	int load_count();

	void load_ref();
	void unload_ref();
	void release();

	T* get() const;
	T* operator->() const;
	T& operator*() const;
	void operator=(const Ref& other);
	bool operator==(const Ref& other) const;
	operator bool() const;

private:
	void hold(RefCtrl* new_ctrl);

public:
	bool has_loaded = false;

private:
	RefCtrl* control = nullptr;

	template<typename> friend class Ref;
	friend Resource;
};

template<typename T>
Ref<T>::Ref(T* resource) {
	if (!resource)
		return;

	static_assert(
		std::is_base_of_v<Resource, T> == true, 
		"Type must inherit Resource."
	);
	RefCtrl* new_ctrl = new RefCtrl{resource};
	hold(new_ctrl);
}

template<typename T>
Ref<T>::Ref(const Ref& other) {
	hold(other.control);
}

template<typename T>
template<typename U> 
Ref<T>::Ref(
	const Ref<U>& other, 
	std::enable_if_t<std::is_convertible_v<U*, T*>, int>
) {
	hold(other.control);
}

template<typename T>
template<typename U>
Ref<U> Ref<T>::d_cast() {
	U* cast = dynamic_cast<U*>(control->resource);
	Ref<U> ret;
	if (!cast)
		return ret;
	ret.hold(control);
	return ret;
}


template<typename T>
Ref<T>::~Ref() {
	release();
}

template<typename T>
int Ref<T>::ref_count() {
	return control->ref_count;
}

template<typename T>
int Ref<T>::load_count() {
	return control->load_count;
}

template<typename T>
void Ref<T>::load_ref() {
	if (has_loaded || !control)	return;

	has_loaded = true;

	if(control->load_count++ <= 0) {
		control->load_res();
	}
}

template<typename T>
void Ref<T>::unload_ref() {
	if (!has_loaded || !control) return;

	has_loaded = false;

	if (--control->load_count <= 0)
		control->unload_res();
}

template<typename T>
void Ref<T>::release() {
	if (!control) return;
	
	unload_ref();

	if (--control->ref_count <= 0) {
		delete control->resource;
		delete control;
	}

	control = nullptr;
}

template<typename T>
T* Ref<T>::get() const {
	if (!control) return nullptr;
	return dynamic_cast<T*>(control->resource);
}

template<typename T>
T& Ref<T>::operator*() const {
	if (!control) return nullptr;
	return *(control->resource);
}

template<typename T>
T* Ref<T>::operator->() const {
	return get();
}

template<typename T>
void Ref<T>::operator=(const Ref& other) {
	hold(other.control);
}

template<typename T>
bool Ref<T>::operator==(const Ref& other) const {
	return control == other.control;
}

template<typename T>
Ref<T>::operator bool() const {
	return control;
}

template<typename T>
void Ref<T>::hold(RefCtrl* new_ctrl) {
	if (control == new_ctrl) return;
	release();
	
	control = new_ctrl;
	control->ref_count++;
}

}

template <typename T>
std::ostream& operator<<(std::ostream& os, const engine::Ref<T>& r) {
	if (!r)
		return os << "none";
	
	return os << *r.get();
}
