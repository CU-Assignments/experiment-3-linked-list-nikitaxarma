class LRUCache {
public:
struct Node{
    int key, value;
    Node*prev;
    Node*next;
    Node(int k, int v){
        key=k;
        value=v;
        prev=nullptr;
        next=nullptr;
    }
};
    LRUCache(int capacity) {
        this->capacity=capacity;
        head=new Node(-1,-1);
        tail= new Node(-1, -1);
        head->next=tail;
        tail-> prev= head;
        
    }
    
    int get(int key) {
        if(cache.find(key)==cache.end()){
             return -1;
        }
        Node *node=cache[key];
        remove(node);
        insertatfront(node);
        return node->value;
        
    }
    
    void put(int key, int value) {
        if(cache.find(key)!=cache.end()){
            Node*node=cache[key];
            node->value=value;
            remove(node);
            insertatfront(node);
        }
        else{
             if(cache.size()==capacity){
                Node * lru= tail->prev;
                remove(lru);
                cache.erase(lru->key);
                delete(lru);
             }
             Node *newnode=new Node(key, value);
             insertatfront(newnode);
             cache[key]=newnode;
        }
        
    }
    private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node*head;
    Node*tail;
    void insertatfront(Node*node){
        node->next=head->next;
        node->prev=head;
        head->next->prev=node;
        head->next=node;
    }
    void remove(Node*node){
        node->prev->next=node->next;
        node->next->prev=node->prev;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
