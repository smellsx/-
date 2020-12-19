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

size_t num[(HASH_SIZE + 1) * TABLE_SIZE];

for(size_t i=0; i<(HASH_SIZE + 1) * TABLE_SIZE ; i++){
    num[i] = rand() % 999 + 1;
}
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

因结果太长不便显示，此测试结果见上传的附件Insert&Remove.txt中


- ####  Insert功能测试

```C
for (uint64_t i = HASH_SIZE * TABLE_SIZE + 1; 
          i <= (HASH_SIZE + 1) * TABLE_SIZE; i++) {
         hash.insert(num[i-1] , num[i-1]);
}
     hash.Show_all();
     cout<<"*******************"<<endl;
for(size_t i=HASH_SIZE*TABLE_SIZE ; i<(HASH_SIZE+1)*TABLE_SIZE ; i++){
     	hash.remove(num[i]);
}
     hash.Show_all();
     cout<<"******************"<<endl;

```
<img src="https://github.com/smellsx/-/blob/main/images/insert1.PNG" width = "75%">    
<img src="https://github.com/smellsx/-/blob/main/images/insert2.PNG" width = "75%">  


- #### Remove功能测试
```C
for(size_t i=HASH_SIZE*TABLE_SIZE ; i<(HASH_SIZE+1)*TABLE_SIZE ; i++){
     	hash.remove(num[i]);
}
hash.Show_all();
cout<<"******************"<<endl;
for(size_t i = 0 ; i < HASH_SIZE*TABLE_SIZE ; i++ ){
     	hash.remove(num[i]);
}
hash.Show_all();

```

<img src="https://github.com/smellsx/-/blob/main/images/remove1.PNG" width = "75%">    

<img src="https://github.com/smellsx/-/blob/main/images/remove2.PNG" width = "75%">  


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
因结果太长不便显示，此测试结果见上传的附件Search.txt中




  



### 4.自行编写YCSB测试，运行给定的Benchmark数据集并测试OPS(Operations per second)和延迟两个性能指标
|(有回收溢出空间)| time  | 溢出页面 |  OPS|
|------| -------|------------| -----------|
|0-100 load+run | 127.168ms+12.618ms| 2145|  791366|
|25-75 load+run | 110.218ms+10.751ms| 2124|916666|
|50-50 load+run | 136.775ms+12.087ms| 2497|743243|
|75-24 load+run | 125.662ms+11.35ms | 2097|808823|
|100-0 load+run | 138.051ms+10.521ms| 2084|  743243|


------------------------  

|(没有回收溢出空间)| time |溢出页面 |  OPS |
|------| -------|------------| -----------|
|0-100 load+run | 107.168ms+10.876ms| 6489|  940170| 
|25-75 load+run | 111.077ms+10.541ms| 6427|909090|
|50-50 load+run | 109.068ms+10.595ms| 6355|924369|
|75-24 load+run | 111.921ms+10.729ms | 6259|909090|
|100-0 load+run | 109.418ms+10.611ms| 6165|  924369|



### 5.加分项



#### 溢出桶空间回收（10）

采用位图bitmap方式实现  
两个关键函数  
```C
size_t determine_location(size_t* arr);   //返回bitmap中第一个非零元素的位置  

void set_zero(size_t num,size_t* arr);  //将给定位置的元素在位图中置为1
pm_table* PMLHash:: newOverflowTable(uint64_t &offset)
{

	size_t index = determine_location(bitmap);
	//size_t index = meta->overflow_num;
	offset =  8*1024*1024 + index * sizeof(pm_table);
	(meta->overflow_num)++;


	if( offset + sizeof(pm_table) < FILE_SIZE ){

		pm_table* ptable = (pm_table*)( (char*)start_addr + offset );
		ptable->fill_num = 0;
		ptable->next_offset = 0;
		for(size_t i=0; i<TABLE_SIZE ;i++){
	     	(ptable->kv_arr[i]).key = 0;
			(ptable->kv_arr[i]).value = 0;
		}
		return ptable;

	}else{

		perror(" the space of overflow is over!\n");
		exit(1);

	}
}
```

采用了512*64共4K的空间存储位图，开始时全部置为0,每次要申请一个溢出空间时就调用determin_location获得第一个非零元素的位置，据此来申请溢出空间。每次释放溢出空间就调用set_zero将相应位置置为0.
