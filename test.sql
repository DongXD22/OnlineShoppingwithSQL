CREATE TABLE User (
    UserID INT AUTO_INCREMENT PRIMARY KEY,
    UserName VARCHAR(255) NOT NULL,
    Pwd VARCHAR(255),
    Email VARCHAR(255),
    Balance DECIMAL(10, 2) NOT NULL
);

CREATE TABLE Product (
    ProductID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Description TEXT,
    Price DECIMAL(10, 2) NOT NULL,
    Stock INT NOT NULL
);

CREATE TABLE `Order` (
    OrderID INT AUTO_INCREMENT PRIMARY KEY,         -- 订单ID，自增
    UserID INT NOT NULL,                            -- 用户ID，关联用户表
    TotalAmount DECIMAL(10, 2) NOT NULL,            -- 订单总金额
    Sta ENUM('Pending', 'Completed', 'Canceled') DEFAULT 'Pending',  -- 订单状态，默认为 Pending
    CreatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,  -- 订单创建时间，默认为当前时间
    UpdatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, -- 订单更新时间，自动更新
    FOREIGN KEY (UserID) REFERENCES User(UserID)   -- 外键，关联用户表
);

CREATE TABLE OrderItems (
    OrderItemID INT AUTO_INCREMENT PRIMARY KEY,    -- 订单商品ID，自增
    OrderID INT NOT NULL,                           -- 订单ID，关联订单表
    ProductID INT NOT NULL,                         -- 商品ID，关联商品表
    Quantity INT NOT NULL,                          -- 商品数量
    Price DECIMAL(10, 2) NOT NULL,                  -- 商品单价
    Total DECIMAL(10, 2) GENERATED ALWAYS AS (Quantity * Price) STORED,    FOREIGN KEY (OrderID) REFERENCES `Order`(OrderID), -- 外键，关联订单表
    FOREIGN KEY (ProductID) REFERENCES Product(ProductID) -- 外键，关联商品表
);

CREATE TABLE BrowsingHistory (
    HistoryID INT AUTO_INCREMENT PRIMARY KEY,   -- 浏览历史ID，自增
    UserID INT NOT NULL,                        -- 用户ID，关联用户表
    ProductID INT NOT NULL,                     -- 商品ID，关联商品表
    BrowsedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- 浏览时间，默认当前时间
    FOREIGN KEY (UserID) REFERENCES User(UserID), -- 外键，关联用户表
    FOREIGN KEY (ProductID) REFERENCES Product(ProductID) -- 外键，关联商品表
);
