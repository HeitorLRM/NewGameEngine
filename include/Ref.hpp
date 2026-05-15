#pragma once

#include "Resource.hpp"

#include <ostream>
#include <type_traits>

namespace engine {

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
	void hold(Resource* new_resource);
	bool has_loaded = false;

private:
	Resource* resource = nullptr;

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
	hold(resource);
}

template<typename T>
Ref<T>::Ref(const Ref& other) {
	hold(other.resource);
}

template<typename T>
template<typename U> 
Ref<T>::Ref(
	const Ref<U>& other, 
	std::enable_if_t<std::is_convertible_v<U*, T*>, int>
) {
	hold(other.resource);
}

template<typename T>
template<typename U>
Ref<U> Ref<T>::d_cast() {
	U* cast = dynamic_cast<U*>(resource);
	Ref<U> ret;
	if (!cast)
		return ret;
	ret.hold(resource);
	return ret;
}


template<typename T>
Ref<T>::~Ref() {
	release();
}

template<typename T>
void Ref<T>::load_ref() {
	if (has_loaded || !resource) return;

	has_loaded = true;

	if (resource->load_count++ <= 0) {
		resource->load();
	}
}

template<typename T>
void Ref<T>::unload_ref() {
	if (!has_loaded || !resource) return;

	has_loaded = false;

	if (--resource->load_count <= 0) {
		resource->unload();
	}
}

template<typename T>
void Ref<T>::release() {
	if (!resource) return;
	
	unload_ref();

	if (--resource->ref_count <= 0) {
		delete resource;
	}

	resource = nullptr;
}

template<typename T>
T* Ref<T>::get() const {
	if (!resource) return nullptr;
	return dynamic_cast<T*>(resource);
}

template<typename T>
T& Ref<T>::operator*() const {
	if (!resource) return nullptr;
	return *resource;
}

template<typename T>
T* Ref<T>::operator->() const {
	return get();
}

template<typename T>
void Ref<T>::operator=(const Ref& other) {
	hold(other.resource);
}

template<typename T>
bool Ref<T>::operator==(const Ref& other) const {
	return resource == other.resource;
}

template<typename T>
Ref<T>::operator bool() const {
	return resource;
}

template<typename T>
void Ref<T>::hold(Resource* new_resource) {
	if (resource == new_resource) return;

	release();
	
	resource = new_resource;
	if (resource) {
		resource->ref_count++;
	}
}

}

template <typename T>
std::ostream& operator<<(std::ostream& os, const engine::Ref<T>& r) {
	if (!r)
		return os << "none";
	
	return os << *r.get();
}
