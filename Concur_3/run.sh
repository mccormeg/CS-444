#!/bin/bash
clear
echo "Making problem one.."
make prob1
echo "Running problem one.."
prob1
echo "Making problem two.."
make prob2
echo "Running problem two.."
prob2
echo "Cleaning up..."
make clean
