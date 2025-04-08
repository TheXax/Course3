import unittest
from task_manager import TaskManager

class TestTaskManager(unittest.TestCase):

    def setUp(self):
        self.manager = TaskManager()

    def test_add_task(self):
        response = self.manager.add_task("Сдать лабу")
        self.assertEqual(response, "Task added")
        self.assertIn("Сдать лабу [✗]", [str(task) for task in self.manager.list_tasks()])

    def test_add_empty_task(self):
        with self.assertRaises(ValueError):
            self.manager.add_task("")

    def test_remove_task(self):
        self.manager.add_task("Сдать лабу")
        response = self.manager.remove_task("Сдать лабу")
        self.assertEqual(response, "Task removed")
        self.assertNotIn("Сдать лабу [✗]", [str(task) for task in self.manager.list_tasks()])

    def test_remove_nonexistent_task(self):
        with self.assertRaises(ValueError):
            self.manager.remove_task("Nonexistent task")

    def test_list_tasks(self):
        self.assertEqual(self.manager.list_tasks(), "No tasks available")
        self.manager.add_task("Сдать лабу")
        self.assertEqual([str(task) for task in self.manager.list_tasks()], ["Сдать лабу [✗]"])

    def test_mark_task_completed(self):
        self.manager.add_task("Сдать лабу")
        response = self.manager.mark_task_completed("Сдать лабу")
        self.assertEqual(response, "Task marked as completed")
        self.assertIn("Сдать лабу [✓]", [str(task) for task in self.manager.list_tasks()])

    def test_mark_nonexistent_task_completed(self):
        with self.assertRaises(ValueError):
            self.manager.mark_task_completed("Nonexistent task")

    def test_sort_tasks(self):
        self.manager.add_task("B task")
        self.manager.add_task("A task")
        self.manager.sort_tasks()
        tasks = [str(task) for task in self.manager.list_tasks()]
        self.assertEqual(tasks, ["A task [✗]", "B task [✗]"])

if __name__ == '__main__':
    unittest.main()