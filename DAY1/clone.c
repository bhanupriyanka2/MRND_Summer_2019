//#include<stdio.h>
//#include<stdlib.h>
//struct node {
//	int num;
//	struct node* next;
//	struct node* random;
//};
//
//struct node* createnode(int num) {
//	struct node* newnode = (struct node*)malloc(sizeof(struct node));
//	newnode->num = num;
//	newnode->next = NULL;
//	return newnode;
//}
//
//struct node* cloner_breaker(struct node* head)
//{
//	struct node* temp;
//	head = head->next;
//	temp = head;
//	while (temp->next != NULL)
//	{
//		temp->next = temp->next->next;
//		temp = temp->next;
//	}
//	return head;
//}
//
//struct node* cloner_link(struct node* head)
//{
//	struct node* temp, * random_temp;
//	struct node* ans = (struct node*)malloc(sizeof(struct node));
//	temp = head;
//	while (temp->next->next != NULL)
//	{
//		random_temp = temp->random;
//		if (temp->random == NULL)
//			temp->next->random = NULL;
//		else
//     		temp->next->random = random_temp->next;
//
//		temp = temp->next->next;
//	}
//	random_temp = temp->random;
//	temp->next->random = random_temp->next;
//	ans = cloner_breaker(head);
//	return ans;
//}
//
//struct node* create_clone(struct node* head)
//{
//	struct node* temp, * temp1;
//	struct node* result = (struct node*)malloc(sizeof(struct node));
//	temp = head;
//	while (temp->next != NULL)
//	{
//		struct node* nd = createnode(temp->num);
//		temp1 = temp->next;
//		temp->next = nd;
//		nd->next = temp1;
//		temp = temp->next->next;
//	}
//	struct node* nd = createnode(temp->num);
//	temp->next = nd;
//	nd->next = NULL;
//	result = cloner_link(head);
//	return result;
//}
//
//int main()
//{
//	struct node* head = createnode(1);
//	struct node* two = createnode(2);
//	struct node* three = createnode(3);
//	struct node* four = createnode(4);
//	struct node* five = createnode(5);
//	struct node* six = createnode(6);
//	head->next = two;
//	two->next = three;
//	three->next = four;
//	four->next = five;
//	five->next = six;
//	six->next = NULL;
//	head->random = three;
//	two->random = five;
//	three->random = six;
//	four->random = five;
//	five->random = NULL;
//	six->random = four;
//	struct node *result = create_clone(head);
//	struct node* temp = result;
//	while (temp->next != NULL)
//	{
//		printf("data:%d\n", temp->num);
//		if(temp->random!=NULL){
//		  printf("random data:%d\n",temp->random->num);
//		}
//		temp = temp->next;
//	}
//	printf("%d", temp->num);
//	getchar();
//	return 0;
//}