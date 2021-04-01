
#include "palm_features.hpp"
#include "partitioning.hpp"

/*
create fs ( no of hands)
save ( fs)
load fs
search_fs = fs("18728317628731628")
search_result []
new View = partition(fs, m, n) 
loop row in View.rows
    loop col in row.columns
        task search (row, col, search_fs, search_result)
wait_for_all(tasks)
dump search_results
dump timings
dump memory usage

test_params : 
    M=Hands=[100,1000,10000], N=features_per_set=[50,100,200,300], bytes_per_feature=64
    partitions  m = [M/10, M/20, M/100]
                n = [N/10, N/20, ... ]
                features_per_partition = [5,10]
                hands_per_partition = [100, 500, 1000]

*/
/*
Tasks
    task_group : 
        [m,n] tasks_ij
        stop_signal [m]
    search_task ( row, col, fs, res[])
        for f in fs.features
            if  stop_signal[row].stop_requested: break
            found = false
            for h in part(row,col).hands
                if  stop_signal[row].stop_requested: break
                for f in part(row,col).features
                    if  stop_signal[row].stop_requested: break
                    found = compare f, fs
            if !found: set stop_signal[row]   // none of the hands has the feature f
            
            
                
*/
/*
unit tests
1-
    create f1 "17265371625"
    save binary f1
    save text f1    
2-
    create N=10 f1-f10 with strings
    save binary 
    save text
    load binary 
    verify
        save text2 
        assert diff text text2 == 0 
    load text verify
3-
    create N=10,20 f1,...,fi,...,fN
    byte_i_j = i * 64 + j , for example
    create M=100 fs
    save binary
    load binary 
    verify
4- compare f1-x and f1-y
    create f1 "234234"
    create f2 "09586098"
    compare f1 ,f2
    assert == 
    assert != 
5- compare fs1 fs2
    create fs1 "12312"
    create fs2 "12342"
    compare fs1 fs2
    assert ==
    assert != 
6-containers and iterators
    f-set 1:300
    f-array i:i+k
    view.part_at(i,j)
    view.rows
    view.row_at(r)
    view.columns
    view.column_at(j)
    view.all_features
    partition.hands
    partition.hand_at(h)
    partition.features
    partition.feature_at(i)
    hand.features
    hand.feature_at(i)
    feature.bytes
    feature.byte_at(i)
    features.find_by_id(id)->feature
7- feature set or f-array manipulation
    insert_at(i)
    remove_at(i)
    append()
    update_at(i)
    swap_at(i,j)
8- database operations
    create required folders/files
    import  overwrite/append
    export
    add features
    remove features
    update features
    save partition i..j
    load partition i..j
9- search tests, sequential
    for database size : a, b, c
        for hf in hands = [hf_1,.. , hf_p]
            search dbase hf
            verify result
                assert !found
                assert found exact one
                assert found many 

10- search tests, parallel
    for database size : a, b, c
        for partition in [rows only, columns only,row-col 2D]
            for hf in hands = [hf_1,.. , hf_p]
                search dbase hf
                verify result
                    assert !found
                    assert found exact one
                    assert found many 


    


11- statiistic analysis of timings and memory ... 

*/