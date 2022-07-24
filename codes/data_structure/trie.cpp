const int ALPHABET_SIZE = 10;
const char datStart = 'a'; // change this to 0 or A
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};
  
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
  
    pNode->isEndOfWord = false;
  
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
  
    return pNode;
}
  
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - datStart;
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
  
        pCrawl = pCrawl->children[index];
    }
  
    pCrawl->isEndOfWord = true;
}
  
bool search(struct TrieNode *root, string key){
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - datStart;
        if (!pCrawl->children[index])
            return false;
  
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->isEndOfWord;
}
