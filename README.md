# 数据库实验报告   小组成员：柴百里_18341004 王圣汐_18341034 张爽_18341047



### 1.根据[Intel的教程](https://software.intel.com/content/www/us/en/develop/articles/how-to-emulate-persistent-memory-on-an-intel-architecture-server.html)，利用普通内存模拟NVM环境并测试是否配置正确

​                                                                                                                                                                           

​    



### 2.根据PMDK的README安装教程进行库安装

​                                                                                                                                                                                          

​       



### 3.根据项目框架和需求实现代码并运行，测试每个功能运行并截图相应结果

​      

#### 测试代码 insert & remove


```C
for(size_t i=0 ; i<HASH_SIZE+1 ; i++){
     	cout<<"insert" <<i<<"*****************"<<endl;
     	for(size_t j=0; j<TABLE_SIZE ; j++){
     		hash.insert( num[i*HASH_SIZE + j]  , num[i*HASH_SIZE + j] );
     	}
     	hash.Show_all();
     	cout<<endl;
}
     
for(size_t i=0 ; i<HASH_SIZE+1 ; i++){
     	cout<<"remove" <<i<<"*****************"<<endl;
     	for(size_t j=0; j<TABLE_SIZE ; j++){
     		hash.remove( num[i*HASH_SIZE + j] );
     	}
     	hash.Show_all();
     	cout<<endl;
}
```



这里我们给了一个有17个insert和17个remove操作的数据集，然后去执行相应的操作



- ####  Insert功能测试



<img src="https://github.com/smellsx/-/blob/main/images/insert1.PNG" width = "100%">  


- #### Remove功能测试




#### 测试代码 Search


```C
for(size_t i=0 ; i < (HASH_SIZE + 1) * TABLE_SIZE ; i++){
     	size_t val;
     	hash.search(num[i] , val);
     	cout<<"******"<<endl;
     	cout << "key: " << num[i] << "\nvalue: " << val << endl;
     	if(num[i] != val){
     		cout<<"error!"<<endl;
     		break;
     	}
}
```



- #### Search功能测试






- #### Update功能测试


  



### 4.自行编写YCSB测试，运行给定的Benchmark数据集并测试OPS(Operations per second)和延迟两个性能指标





### 5.加分项



#### 溢出桶空间回收（10）



