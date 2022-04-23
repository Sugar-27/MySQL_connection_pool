# MySQL_connection_pool
利用C++11语法特性写的一个跨平台数据库连接池

## 关键技术点
MySQL数据库编程、单例模式、queue队列容器、C++11多线程编程、线程互斥、线程同步通信和unique_lock、基于CAS的原子整形、智能指针shared_ptr、lambda表达式、生产者-消费者线程模型

## 项目背景
为了提高MySQL数据库（基于C/S设计）的访问瓶颈，除了在服务器端增加缓存服务器缓存常用的数据之外（例如redis），还可以增加连接池，来提高MySQL Server的访问效率，在高并发情况下，大量的TCP三次握手、MySQL Server连接认证、MySQL Server关闭连接回收资源和TCP四次挥手所耗费的性能时间也是很明显的，增加连接池就是为了减少这一部分的性能损耗，数据库连接池的存在使得项目不需要频繁的进行上述操作而只需要专注于增删改查即可。

## 主要实现功能
目前规划功能为四个：
* 初始连接量（initSize）：表示连接池事先会和MySQL Server创建initSize个数的connection连接，当应用发起MySQL访问时，不用再创建和MySQL Server新的连接，直接从连接池中获取一个可用的连接就可以，使用完成后，并不去释放connection，而是把当前connection再归还到连接池当中。

* 最大连接量（maxSize）：当并发访问MySQL Server的请求增多时，初始连接量已经不够使用了，此 时会根据新的请求数量去创建更多的连接给应用去使用，但是新创建的连接数量上限是maxSize，不能无限制的创建连接，因为每一个连接都会占用一个socket资源，一般连接池和服务器程序是部署在一台 主机上的，如果连接池占用过多的socket资源，那么服务器就不能接收太多的客户端请求了。当这些连 接使用完成后，再次归还到连接池当中来维护。

* 最大空闲时间（maxIdleTime）：当访问MySQL的并发请求多了以后，连接池里面的连接数量会动态 增加，上限是maxSize个，当这些连接用完再次归还到连接池当中。如果在指定的maxIdleTime里面， 这些新增加的连接都没有被再次使用过，那么新增加的这些连接资源就要被回收掉，只需要保持初始连 接量initSize个连接就可以了。

* 连接超时时间（connectionTimeout）：当MySQL的并发请求量过大，连接池中的连接数量已经到达 maxSize了，而此时没有空闲的连接可供使用，那么此时应用从连接池获取连接无法成功，它通过阻塞 的方式获取连接的时间如果超过connectionTimeout时间，那么获取连接失败，无法访问数据库。

## 基本操作：
执行`create_sql.sql`中的SQL语句创建MySQL数据库，然后编译`test.cpp`，编译语句`g++ test.cpp -o test -lmysqlclient`，编译完成后使用root用户执行`test`程序，再次查询表chat.user可以看到数据增加了一行。
