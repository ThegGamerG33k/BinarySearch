// ordered_set.h
#include "array_list.h"

namespace ssuds
{
	enum class SortOrder { preorder, postorder, inorder };

	template <class T>
	class OrderedSet
	{
	protected:
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;
			// Node* mParent;


			Node(const T& val) : mData(val), mLeft(nullptr), mRight(nullptr)
			{
				// empty
			}

			~Node()
			{
				if (mLeft)
				{
					delete mLeft;
				}
				if (mRight)
				{
					delete mRight;
				}
			}

			bool insert_recursive(const T& val)
			{
				// I'm a node in the tree.  Add this thing under me
				if (val < mData)
				{
					// The new node should go to my left
					if (mLeft == nullptr)
					{
						// We don't have a left child -- make one!
						mSize++;
						mLeft = new Node(val);
						return true;
					}
					else
					{
						// We do have a left child -- let it finish the process
						// Note: we DO have the chance in really large trees, that we exceed the stack memory
						mLeft->insert_recursive(val);
					}
				}
				else if (val > mData)
				{
					// The new node should go to my right
					if (mRight == nullptr)
					{
						// We don't have a right child -- make one!
						mSize++;
						mRight = new Node(val);
						return true;
					}
					else
					{
						// We do have a right child -- let it finish the process
						mRight->insert_recursive(val);
					}
				}
				else
				{
					// We HOLD that value.  This is a duplicate.  
					return false;
				}
			}
			void erase_recursive(const T& val)
			{
				if (val < mData)
				{
					// is the value to the left equal to what we're looking for
					if (mLeft == val)
					{
						// It is, so we delete the item and decrease the size of the tree
						delete mLeft;
						mSize--;
					}
					else
					{
						// We do have a left child -- let it finish the process
						// Note: we DO have the chance in really large trees, that we exceed the stack memory
						mLeft->insert_recursive(val);
					}
				}
				else if (val > mData)
				{
					// is the value to the right equal to what we're looking for
					if (mRight == val)
					{
						// It is, so we delete the item and decrease the size of the tree
						delete mRight;
						mSize--;
					}
					else
					{
						// We do have a right child -- let it finish the process
						mRight->insert_recursive(val);
					}
				}
				else
				{
					// We HOLD that value.  We don't have this value in the tree
					return false;
				}
			}

			int height_recursive()
			{
				int count = 1;
				int right = 1;
				int left = 1;
				// I'm a node in the tree.  If I have no children, set count to one
				if (mLeft == nullptr && mRight == nullptr)
				{
					return count;
				}

				else
				{
					if (mRight != nullptr)
					{
						right = mRight->height_recursive();
					}
					else
						right = 0;

					if (mLeft != nullptr)
						left = mLeft->height_recursive();
					else
						left = 0;

					if (left < right)
					{
						return right;
					}
					else (left >= right)
					{
						return left;
					}
				}
			}

			int size_recursive()
			{
				int count = 1;
				int right = 1;
				int left = 1;
				// I'm a node in the tree.  If I have no children, set count to one
				if (mLeft == nullptr && mRight == nullptr)
				{
					return count;
				}

				else
				{
					if (mRight != nullptr)
					{
						right = mRight->size_recursive();
					}
					else
						right = 0;

					if (mLeft != nullptr)
						left = mLeft->size_recursive();
					else
						left = 0;
				}
				return right + left;
			}

			void trav_pre(ArrayList<T>& ref)
			{
				ref.append(mData);
				if (mLeft)
					mLeft->trav_pre();
				if (mRight)
					mRight->trav_pre();
			}
			
			void trav_in(ArrayList<T>& ref)
			{
				if (mLeft)
					mLeft->trav_in();
				ref.append(mData);
				if (mRight)
					mRight->trav_in();
			}

			void trav_post(ArrayList<T>& ref)
			{
				if (mLeft)
					mLeft->trav_post();
				if (mRight)
					mRight->trav_post();
				ref.append(mData);
			}
		};

		Node* mRoot;
		unsigned int mSize;

	public:
		OrderedSet() : mSize(0), mRoot(nullptr)
		{
			// empty
		}

		~OrderedSet()
		{
			clear();
		}

		bool erase(const T& val)
		{
			if (size == 0)
			{
				return false;
			}
			else
			{
				mRoot->erase_recursive(val);
			}
		}

		int get_height()
		{
			if (mSize == 0)
			{
				return 0;
			}

			else
			{
				mRoot->height_recursive();
			}
		}

		int size()
		{
			if (mSize == 0)
				return 0;

			else
			{
				mRoot->size_recursive();
			}
		}

		void clear()
		{
			if (mRoot)
				delete mRoot;
		}

		bool contains(const T& val)
		{

		}

		void rebalance()
		{

		}

		ssuds::ArrayList<T> Traverse(SortOrder order)
		{
			if (order == SortOrder::preorder)
			{
				ArrayList<T> list = ();
				mRoot->trav_pre(list);
				
			}

			if (order == SortOrder::postorder)
			{
				mRoot->trav_post();
			}

			if (order == SortOrder::inorder)
			{
				mRoot->trav_in();
			}
		}

		bool insert(const T& val)
		{
			// return true if we really added something.
			if (mSize == 0)
			{
				// This is the first item.  Make it the root
				mRoot = new Node(val);
				mSize = 1;
				return true;
			}
			else
			{
				// There is already a root.  Use recursion to add
				mRoot->insert_recursive(val);
			}
		}

		
	};
}