struct heap
{
    int heap[MAXV][2], v2n[MAXV];
    int size;

    void init(int sz)
    {
        size = sz;
        for(int i = 0; i < size; i++) {
            heap[i][1] = v2n[i] = i;
            heap[i][0] = 0x3f3f3f3f;
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
        swap(v2n[heap[a][1]], v2n[heap[b][1]]);
        swap(heap[a][0], heap[b][0]);
	swap(heap[a][1], heap[b][1]);
    }

    int extract_min()
    {
        int ret = heap[0][1];
        s(0, --size);

        int cur_pos = 0;
        while(true) {
            int min = heap[cur_pos][0], pos_min = cur_pos;
            for(int i = 1; i <= 2; i++)
                if(2*cur_pos + i < size && heap[2*cur_pos + i][0] < min) {
                    min = heap[2*cur_pos + i][0];
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
        heap[v2n[vertex]][0] = new_value;

        int cur_pos = v2n[vertex];
        while(cur_pos >= 1) {
            int parent = (cur_pos - 1)/2;
            if(heap[cur_pos][0] >= heap[parent][0])
                break;

            s(cur_pos, parent);
            cur_pos = parent;
        }
    }
};

