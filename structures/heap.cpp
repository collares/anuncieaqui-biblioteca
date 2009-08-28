struct heap
{
    //n2v = treenode_to_vertex, v2n = vertex_to_treenode
    int heap[MAXV], n2v[MAXV], v2n[MAXV];
    int size;

    void init(int sz)
    {
        size = sz;
        for(int i = 0; i < size; i++) {
            n2v[i] = v2n[i] = i;
            heap[i] = 0x3f3f3f3f;
        }
    }

    void swap(int& a, int& b) __attribute__((always_inline))
    {
        int temp;
        temp = a;
        a = b;
        b = temp;
    }

    void s(int a, int b) __attribute__((always_inline))
    {
        swap(heap[a], heap[b]);
        swap(v2n[n2v[a]], v2n[n2v[b]]);
        swap(n2v[a], n2v[b]);
    }

    int extract_min()
    {
        int ret = n2v[0];
        s(0, --size);

        int cur_pos = 0;
        while(true) {
            int min = heap[cur_pos], pos_min = cur_pos;
            for(int i = 1; i <= 2; i++)
                if(2*cur_pos + i < size && heap[2*cur_pos + i] < min) {
                    min = heap[2*cur_pos + i];
                    pos_min = 2*cur_pos + i;
                }

            if(cur_pos == pos_min)
                break;

            s(cur_pos, pos_min);
            cur_pos = pos_min;
        }

        return ret;
    }

    int decrease_key(int vertex, int new_value)
    {
        heap[v2n[vertex]] = new_value;

        int cur_pos = v2n[vertex];
        while(cur_pos >= 1)
        {
            int parent = (cur_pos - 1)/2;
            if(heap[cur_pos] >= heap[parent])
                break;

            s(cur_pos, parent);
            cur_pos = parent;
        }
    }
};
