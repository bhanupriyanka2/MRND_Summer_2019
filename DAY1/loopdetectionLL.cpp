//#include <stdio.h>
//#include <stdlib.h>
//
//struct node{
//	int data;
//	struct node *next;
//};
//
//struct node *create_node(int data){
//	struct node *new_node = (struct node *)malloc(sizeof(struct node));
//	new_node->data = data;
//	new_node->next = NULL;
//	return new_node;
//}
//
//struct node *create_list(struct node *head, struct node *new_node){
//	if (head == NULL){
//		head = new_node;
//		return head;
//	}
//	struct node *temp = head;
//	while (temp->next != NULL){
//		temp = temp->next;
//	}
//	temp->next = new_node;
//	return head;
//}
//
//struct node *meetingPointInLoop(struct node *head){
//	if (head == NULL){
//		return NULL;
//	}
//	struct node *pfast = head,*pslow = head;
//	while (pfast != NULL && pslow != NULL){
//		pslow = pslow->next;
//		pfast = pfast->next->next;
//		if (pfast == pslow)
//			break;
//	}
//	if (pfast == NULL || pslow == NULL){
//		return NULL;
//	}
//	return pfast;
//}
//
//struct node *startingPointOfLoop(struct node *head){
//	if (head == NULL)
//		return NULL;
//	struct node *meetingPoint = meetingPointInLoop(head);
//	struct node *startingNode = head;
//	while (startingNode == meetingPoint){
//		startingNode = startingNode->next;
//		meetingPoint = meetingPoint->next;
//	}
//	return startingNode;
//}
//
////int main(){
////	int nodes, data;
////	printf("Enter number of nodes in the list:");
////	scanf("%d", &nodes);
////	fflush(stdin);
////	printf("Enter the nodes in list:");
////	struct node *head = NULL;
////	struct node *new_node = NULL;
////	for (int nodeNum = 0; nodeNum < nodes; nodeNum++){
////		scanf("%d", &data);
////		new_node = create_node(data);
////		head = create_list(head, new_node);
////	}
////	struct node *temp = head,*ptr=head;
////	while (temp->next != NULL){
////		temp = temp->next;
////	}
////	int count = 0;
////	while (count < 2){
////		count++;
////		ptr = ptr->next;
////	}
////	temp->next = ptr;
////	fflush(stdin);
////	struct node *result = meetingPointInLoop(head);
////	struct node *result1 = startingPointOfLoop(head);
////	if (result != NULL){
////		printf("Data at meeting point of 2 pointers:%d\n", result->data);
////	}
////	else{
////		printf("List contains no loop");
////	}
////	if (result1 != NULL){
////		printf("Data at starting point of loop:%d", result1->data);
////	}
////	else{
////		printf("List contains no loop");
////	}
////	getchar();
////	return 0;
////}