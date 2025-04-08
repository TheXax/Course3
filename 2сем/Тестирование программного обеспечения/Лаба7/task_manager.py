from task import Task

class TaskManager:
    def __init__(self):
        self.tasks = []

    def add_task(self, task):
        if not task:
            raise ValueError("Task cannot be empty")
        self.tasks.append(Task(task))
        return "Task added"

    def remove_task(self, task):
        for t in self.tasks:
            if t.name == task:
                self.tasks.remove(t)
                return "Task removed"
        raise ValueError("Task not found")

    def list_tasks(self):
        return self.tasks if self.tasks else "No tasks available"

    def mark_task_completed(self, task):
        for t in self.tasks:
            if t.name == task:
                t.mark_completed()
                return "Task marked as completed"
        raise ValueError("Task not found")

    def sort_tasks(self):
        self.tasks.sort(key=lambda x: x.name)
        return "Tasks sorted"


if __name__ == "__main__":
    manager = TaskManager()
    
    while True:
        print("\nTask Manager")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. List Tasks")
        print("4. Mark Task as Completed")
        print("5. Sort Tasks")
        print("6. Exit")
        choice = input("Choose an option: ")

        if choice == '1':
            task = input("Enter task: ")
            print(manager.add_task(task))
        elif choice == '2':
            task = input("Enter task to remove: ")
            try:
                print(manager.remove_task(task))
            except ValueError as e:
                print(e)
        elif choice == '3':
            print("Tasks:", manager.list_tasks())
        elif choice == '4':
            task = input("Enter task to mark as completed: ")
            try:
                print(manager.mark_task_completed(task))
            except ValueError as e:
                print(e)
        elif choice == '5':
            print(manager.sort_tasks())
        elif choice == '6':
            break
        else:
            print("Invalid option")