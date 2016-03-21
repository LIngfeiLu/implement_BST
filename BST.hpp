/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
*/


#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;
template<typename Data>
class BST {

  protected:

    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data>* root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

  public:

    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
      Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {  }


    /** Default destructor.
      Delete every node in this BST.
     */ // TODO
    virtual ~BST() {
      //call deleteAll, and set root, isize and iheight to 0
      //since it is destructed
      deleteAll(root);
      root = 0;
      isize = 0;
      iheight = 0;
    }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' or "==" operator when comparing
     *  Data items. (should not use >, <=, >=)
     */
    virtual bool insert(const Data& item) {
      BSTNode<Data> *cur_node = root;
      BSTNode<Data> *new_node = new BSTNode<Data>(item);
      //update temp_height every while loop,
      //if temp_height > iheight, update iheight/
      int temp_height = 0; 
      
      //if root is not 0, then enter the the while loop 
      while(root){
        //current node data less than passed in data
        if(cur_node->data < item){
          if(cur_node->right){
            //if current node has right child, enter right child
            cur_node = cur_node->right;
            temp_height++;
            if(temp_height > iheight) iheight = temp_height;
          }
          else{
            //current node has no child, then passed in data should be its child
            cur_node->right = new_node;
            new_node->parent = cur_node;
            isize++;
            temp_height++;
            if(temp_height > iheight) iheight = temp_height;
            return true;
          }
        }
        else if(cur_node->data == item){
          //if current node data equals to passed in data, then return false
          delete new_node;
          //must free new_node in case of memory leak
          new_node = 0;
          return false;
        }
        else{
          if(cur_node->left){
            //if current node has left child, enter left child
            cur_node = cur_node->left;
            temp_height++;
            if(temp_height > iheight) iheight = temp_height;
          }
          else{
            //current node has no child, then passed in data should be its child
            cur_node->left = new_node;
            new_node->parent = cur_node;
            isize++;
            temp_height++;
            if(temp_height > iheight) iheight = temp_height;
            return true;
          }
        }
      }
      //if did not enter while loop, then root is 0, then set new_node to root
      root = new_node;
      isize++;
      return true;
    }


    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' or "==" operator when comparing
     *  Data items. (should not use >, <=, >=)
     */ // TODO
    iterator find(const Data& item) const {
      //start from the root
      BSTNode<Data> *output = root;
      //if output is not null and output->data not equal to item
      //if did not enter while, then either root is null, or data == item
      while(output && !(output->data == item)){
        //if data < item, then go to its right
        if(output->data < item)
          output = output->right;
        //if data > item, then go to its left
        else
          output = output->left;
      }
      //if output is not null, then return iterator pointing to output 
      if(output)  return typename BST<Data>::iterator(output);
      //if output is null, then return iterator pointing to null
      else  return end();
    }


    /** Return the number of items currently in the BST.
     */ // TODO
    unsigned int size() const {
      return isize; 
    }

    /** Return the height of the BST.
     */ // TODO
    unsigned int height() const {
      return iheight;
    }


    /** Return true if the BST is empty, else false.
     */ // TODO
    bool empty() const {
      return (isize == 0);
    }

    /** Return an iterator pointing to the first item in the BST (not the root).
     */ // TODO
    iterator begin() const {
      //start from the root
      BSTNode<Data> *node = root;
      //to its most left child
      while(node && node->left){
        node = node->left;
      }
      //return the iterator pointing to BST first element.
      return typename BST<Data>::iterator(node);
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const {
      return typename BST<Data>::iterator(0);
    }

    /** Perform an inorder traversal of this BST.
     */
    void inorder() const {
      inorder(root);
    }


  private:

    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
     */ // TODO
    void inorder(BSTNode<Data>* n) const {
      /* Pseudo Code:
         if current node is null: return;
         recursively traverse left sub-tree
         print current node data
         recursively traverse right sub-tree
       */
      //if n is null, return
      if(!n)  return;
      //print the smaller element
      inorder(n->left);
      //print the middle element
      std::cout << n->data << "\n";
      //print the larger element
      inorder(n->right);
      return;
    }

    /** Find the first element of the BST
     */ 
    static BSTNode<Data>* first(BSTNode<Data>* root) {
      if(root == 0) return 0;
      while(root->left != 0) root = root->left;
      return root;
    }

    /** do a postorder traversal, deleting nodes
     */ // TODO
    static void deleteAll(BSTNode<Data>* n) {
      /* Pseudo Code:
         if current node is null: return;
         recursively delete left sub-tree
         recursively delete right sub-tree
         delete current node
       */
      if(!n)  return;
      //delete left child
      deleteAll(n->left);
      //delete right child
      deleteAll(n->right);
      //delet itself
      delete n;
      n = 0;
    }


};


#endif //BST_HPP

