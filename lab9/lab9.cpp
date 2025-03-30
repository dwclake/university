/*
 *  CSCI 115 - 03
 *  Lab 9
 *
 *  Devon Webb
 */

#include <cstdio>
#include <tuple>

#include "Bst.h"

int main() {
  // Case one
  std::printf("Case 1:\n");
  auto root1 = new Bst::Node<int>(20);

  Bst::insert(root1, 10);
  Bst::insert(root1, 15);

  Bst::print_level(root1, 0);
  std::cout << std::endl;
  Bst::print_level(root1, 1);
  std::cout << std::endl;
  Bst::print_level(root1, 2);
  std::cout << std::endl << std::endl;
  
  std::cout << "left rotate around 10, right rotate around 20" << std::endl;
  root1->left = Bst::rotate_left(root1->left);
  root1 = Bst::rotate_right(root1);

  Bst::print_level(root1, 0);
  std::cout << std::endl;
  Bst::print_level(root1, 1);
  std::cout << std::endl;
  
  delete root1;

  // Case two
  std::printf("\nCase 2:\n");
  auto root2 = new Bst::Node<int>(10);

  Bst::insert(root2, 5);
  Bst::insert(root2, 1);

  Bst::print_level(root2, 0);
  std::cout << std::endl;
  Bst::print_level(root2, 1);
  std::cout << std::endl;
  Bst::print_level(root2, 2);
  std::cout << std::endl << std::endl;
  
  std::cout << "right rotate around 10" << std::endl;
  root2 = Bst::rotate_right(root2);
  
  Bst::print_level(root2, 0);
  std::cout << std::endl;
  Bst::print_level(root2, 1);
  std::cout << std::endl;
  
  delete root2;

  // Case three
  std::printf("\nCase 3:\n");
  auto root3 = new Bst::Node<int>(10);

  Bst::insert(root3, 20);
  Bst::insert(root3, 30);

  Bst::print_level(root3, 0);
  std::cout << std::endl;
  Bst::print_level(root3, 1);
  std::cout << std::endl;
  Bst::print_level(root3, 2);
  std::cout << std::endl << std::endl;
  
  std::cout << "left rotate around 10" << std::endl;
  root3 = Bst::rotate_left(root3);
  
  Bst::print_level(root3, 0);
  std::cout << std::endl;
  Bst::print_level(root3, 1);
  std::cout << std::endl;
  
  delete root3;

  // Case four
  std::printf("\nCase 4:\n");
  auto root4 = new Bst::Node<int>(10);

  Bst::insert(root4, 20);
  Bst::insert(root4, 30);

  Bst::print_level(root4, 0);
  std::cout << std::endl;
  Bst::print_level(root4, 1);
  std::cout << std::endl;
  Bst::print_level(root4, 2);
  std::cout << std::endl << std::endl;
  
  std::cout << "left rotate around 10" << std::endl;
  root4 = Bst::rotate_left(root4);
  
  Bst::print_level(root4, 0);
  std::cout << std::endl;
  Bst::print_level(root4, 1);
  std::cout << std::endl;

  delete root4;
}
