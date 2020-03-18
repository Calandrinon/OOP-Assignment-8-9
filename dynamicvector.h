#ifndef __DYNAMICVECTOR_H__
#define __DYNAMICVECTOR_H__
#include <cstdlib>

template <class T>
class DynamicVector {
    private:
        T *array;
        int number_of_elements;


    public:
        DynamicVector() {
        	this->array = (T*)malloc(sizeof(T));
        	this->number_of_elements = 0;
        }


        void push_back(T element) {
        	array[number_of_elements] = element;
        	number_of_elements++;

        	T* new_array = (T*)malloc(sizeof(T)*(number_of_elements+1));
        	for (int i = 0; i < number_of_elements; i++)
        		new_array[i] = array[i];

			free(array);
        	array = new_array;
        }
		

		void remove(int index, int elements_to_delete) {
			if (index + elements_to_delete >= number_of_elements)
				throw "IndexError: Can't delete elements outside of range!\n";

			T* new_array = (T*)malloc(sizeof(T)*(number_of_elements-elements_to_delete+1));
			for (int i = 0; i < index; i++)
				new_array[i] = array[i];

			for (int i = index + elements_to_delete; i < number_of_elements; i++)
				new_array[i-elements_to_delete]=array[i];

			free(array);	
			array = new_array;

			number_of_elements -= elements_to_delete;
		}


		T element(int index) {
			/**
			 * Returns the element at index "index" in the 
			 * dynamic vector.
			 *
			 * Input:
			 * 	- index: int
			 *
			 * Output:
			 * 	- an element of type T from the index "index"
			 *
			 * **/
			
			if (index >= number_of_elements) {
				throw "IndexError";		
			}

			return array[index];
		}


		int size() {
			return number_of_elements;	
		}


        void free_vector() {	
        	free(array);
        }
};



#endif
