<h1>VapeShop POS System</h1>

## Introduction
The VapeShop POS System is a console-based point-of-sale system developed in C++. It serves as a comprehensive solution for managing transactions, inventory, and sales in a vape shop. The system utilizes file streams as a database for storing and retrieving information.

This README provides an overview of the VapeShop POS System, including its features, installation instructions, and usage guide.

## Features
The VapeShop POS System offers the following key features:

1. **Inventory Management:** Easily manage your vape shop's inventory, including adding new products, updating quantities, and removing items.

2. **Sales Transactions:** Conduct sales transactions, calculate totals, and generate itemized receipts for customers.

3. **Customer Information:** Store and retrieve customer information, including names, contact details, and purchase history.

4. **Reporting:** Generate reports to analyze sales data, track popular products, and identify trends.

5. **Search and Filter:** Search for specific products or customers, and filter sales transactions based on various criteria.

6. **Data Persistence:** Utilize file streams as a persistent database to store inventory, customer, and transaction information.

## Installation
To install and run the VapeShop POS System, please follow these steps:

1. Clone the repository or download the source code.

2. Ensure that you have a C++ compiler installed on your system.

3. Open the project folder in Visual Studio Code and open terminal.

4. Compile the code using the following command:

```terminal
cd "\src"; if ($?) { g++ *.cpp -o main } ; if ($?) { .\main }
```

5. Run the executable.

## Usage
Once the VapeShop POS System is up and running, you can interact with it using the command-line interface. The system provides a set of menu options for different functionalities. Use the keyboard to select and execute the desired actions.

## Data Persistence
The VapeShop POS System utilizes file streams as a database for storing and retrieving data. The system creates and maintains the following files:

* **inventory.txt:** Stores information about products in the inventory.
* **admins.txt:** Contains admins credentials.
* **users.txt:** Contains customer credentials.
* **transactions.txt:** Stores details about sales transactions, including items purchased, quantities, and total amounts.
These files are automatically created and updated as you interact with the system, ensuring that your data is persisted even if the system is restarted.

## Contributions
Contributions to the VapeShop POS System are welcome. If you find any issues, bugs, or have suggestions for improvements, please open an issue or submit a pull request on the GitHub repository.

## License
The VapeShop POS System is licensed under the MIT License. Feel free to modify and distribute the code according to the terms of the license.

## Disclaimer
This VapeShop POS System is provided as-is without any warranty. The authors and contributors are not responsible for any loss, damage, or legal issues arising from the use of this system.

Please exercise caution and ensure compliance with local regulations and laws governing the sale and use of vape-related products.
