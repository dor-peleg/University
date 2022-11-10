import collections
from itertools import combinations


class Node:
	"""
	creates a Node objects
	"""
	def __init__(self, data, positive_child=None, negative_child=None):
		self.data = data
		self.positive_child = positive_child
		self.negative_child = negative_child


class Record:
	"""
	creates a Record object
	"""
	def __init__(self, illness, symptoms):
		self.illness = illness
		self.symptoms = symptoms


def parse_data(filepath):
	"""
	reads data from a text file and convert each line to a Record object.
	:param filepath: path to the text file.
	:return: list of all the records objects.
	"""
	with open(filepath) as data_file:
		records = []
		for line in data_file:
			words = line.strip().split()
			records.append(Record(words[0], words[1:]))
		return records


class Diagnoser:
	"""
	create a diagnoser object
	"""
	def __init__(self, root: Node):
		self.root = root
		
	def diagnose(self, symptoms):
		"""
		Diagnoses the disease according to the symptoms list.
		:param symptoms: list of symptoms.
		:return:The diagnosed disease.
		"""
		if self.root.positive_child is None and self.root.negative_child is None:
			return self.root.data
		if self.root.data in symptoms:
			new_root = self.root.positive_child
			new_diagnoser = Diagnoser(new_root)
			decision = new_diagnoser.diagnose(symptoms)
		else:
			new_root = self.root.negative_child
			new_diagnoser = Diagnoser(new_root)
			decision = new_diagnoser.diagnose(symptoms)
		return decision
		
	def calculate_success_rate(self, records):
		"""
		Calculates the success rate of the diagnose
		according to the record objects.
		:param records: list of record objects
		:return: Success rates for diagnosis.
		"""
		if len(records) == 0:
			raise ValueError("The records list is empty")

		successes = 0
		for record in records:
			decision = self.diagnose(record.symptoms)
			if decision == record.illness:
				successes += 1
		return successes / len(records)

	def all_illnesses(self):
		"""
		Returns a list of all diseases in the leaves of the tree.
		:return:list of diseases
		"""
		temp_lst = []
		illnesses_lst = []
		illnesses_dict = self._helper_all_illnesses({})
		for key in illnesses_dict:
			temp_lst.append((key, illnesses_dict[key]))
		temp_lst.sort(key=lambda tup: tup[1], reverse=True)
		for tup in temp_lst:
			illnesses_lst.append(tup[0])
		return illnesses_lst

	def _helper_all_illnesses(self, illnesses_dict):
		"""
		Returns a dictionary where the value of each disease
		is the amount of leaves it appears in
		:param illnesses_dict: Dictionary with the information collected so far
		:return:Dictionary with all the diseases and how many times they appear
		"""
		if self.root.data is None:
			return illnesses_dict
		if not self.root.positive_child and not self.root.negative_child:
			if self.root.data not in illnesses_dict:
				illnesses_dict[self.root.data] = 1
			elif self.root.data in illnesses_dict:
				illnesses_dict[self.root.data] += 1
			return illnesses_dict
		pos_diagnoser = Diagnoser(self.root.positive_child)
		illnesses_dict = pos_diagnoser._helper_all_illnesses(illnesses_dict)
		neg_diagnoser = Diagnoser(self.root.negative_child)
		illnesses_dict = neg_diagnoser._helper_all_illnesses(illnesses_dict)
		return illnesses_dict

	def paths_to_illness(self, illness):
		"""
		Calculates all the ways to get to a particular disease
		through the tree questions
		:param illness: the disease
		:return: A list of all the ways to get to the disease
		"""
		path_lst = self._helper_paths_to_illness(illness, [], [])
		return path_lst

	def _helper_paths_to_illness(self, illness, path, path_lst):
		"""
		A recursive function that checks in every way
		if it reaches the desired disease.
		:param illness:the disease
		:param path: the path so far
		:param path_lst: list of the full paths that leads to thr disease so far
		:return:list of the full paths that leads to thr disease
		"""
		if not self.root.positive_child and not self.root.negative_child:
			if self.root.data == illness:
				path_lst.append(path)
				return path_lst
			else:
				return path_lst
		pos_diagnoser = Diagnoser(self.root.positive_child)
		temp_path = path[:]
		temp_path.append(True)
		path_lst = pos_diagnoser._helper_paths_to_illness(illness, temp_path,
														  path_lst)
		neg_diagnoser = Diagnoser(self.root.negative_child)
		temp_path = path[:]
		temp_path.append(False)
		path_lst = neg_diagnoser._helper_paths_to_illness(illness, temp_path,
														  path_lst)
		return path_lst

	def minimize(self, remove_empty=False):
		"""
		Replaces the tree with a tree where there are no unnecessary
		question nodes
		:param remove_empty: Boolean value, influences the decision which
		nodes are unnecessary
		:return:Boolean value
		"""
		if remove_empty:
			remove_empty_roots = self._minimize_remove_empty()
			if remove_empty_roots == 1:
				self.root = self.root.negative_child
			elif remove_empty_roots == 2:
				self.root = self.root.positive_child
			elif remove_empty_roots == 3:
				self.root = Node(None)

		pos_sub_tree = Diagnoser(self.root.positive_child)
		neg_sub_tree = Diagnoser(self.root.negative_child)

		if self.root.positive_child is None:
			return False
		if pos_sub_tree.minimize():
			self.root.positive_child = self.root.positive_child.positive_child
		if neg_sub_tree.minimize():
			self.root.negative_child = self.root.negative_child.positive_child

		illnesses = self._check_identical_illnesses(pos_sub_tree, neg_sub_tree)
		if illnesses != -1:
			if self._check_paths(illnesses, pos_sub_tree, neg_sub_tree):
				self.root = self.root.positive_child
			return True
		return False

	def _minimize_remove_empty(self):
		"""
		Is called if the remove_empty = True,
		removes question nodes where all the answers lead to None.
		:return: None
		"""
		pos_sub_tree = Diagnoser(self.root.positive_child)
		neg_sub_tree = Diagnoser(self.root.negative_child)

		if self.root.positive_child is None:
			return False
		check_pos_nones = pos_sub_tree._minimize_remove_empty()
		if check_pos_nones == 1:
			self.root.positive_child = self.root.positive_child.negative_child
		elif check_pos_nones == 2:
			self.root.positive_child = self.root.positive_child.positive_child
		elif check_pos_nones == 3:
			self.root.positive_child = Node(None)

		check_neg_nones = neg_sub_tree._minimize_remove_empty()
		if check_neg_nones == 1:
			self.root.negative_child = self.root.negative_child.negative_child
		elif check_neg_nones == 2:
			self.root.negative_child = self.root.negative_child.positive_child
		elif check_neg_nones == 3:
			self.root.negative_child = Node(None)

		empty_root = self._check_empty_illnesses(pos_sub_tree, neg_sub_tree)
		return empty_root

	def _check_identical_illnesses(self, pos_tree, neg_tree):
		"""
		Checks whether a positive and negative response to a symptom
		lead to the same result
		:param pos_tree: A tree where the root is the positive answer
		of the current root
		:param neg_tree: A tree where the root is the negative answer
		of the current root
		:return:If the list of diseases is the same,
		returns the list of diseases.
		If not, returns -1
		"""
		pos_illnesses = pos_tree.all_illnesses()
		neg_illnesses = neg_tree.all_illnesses()
		if pos_illnesses == neg_illnesses:
			return pos_illnesses
		return -1

	def _check_paths(self, illnesses, pos_tree, neg_tree):
		"""
		For each disease, check whether the answers to the questions are the
		same between the positive tree and the negative tree.
		:param illnesses: list of all the illnesses in the tree
		:param pos_tree: A tree where the root is the positive answer
		of the current root
		:param neg_tree: A tree where the root is the negative answer
		of the current root
		:return: True if the answers are identical, False otherwise.
		"""
		for illness in illnesses:
			pos_path = pos_tree.paths_to_illness(illness)
			neg_path = neg_tree.paths_to_illness(illness)
			if pos_path != neg_path:
				return False
		return True

	def _check_empty_illnesses(self, pos_tree, neg_tree):
		"""
		Checks if all the paths in a tree lead to None leaf.
		:param pos_tree: A tree where the root is the positive answer
		of the current root
		:param neg_tree: A tree where the root is the negative answer
		of the current root
		:return:1 if all the paths in the positive tree lead to None leaf
				2 if all the paths in the negative tree lead to None leaf
				3 if both.
		"""
		pos_illnesses = pos_tree.all_illnesses()
		neg_illnesses = neg_tree.all_illnesses()
		if not pos_illnesses and not neg_illnesses:
			return 3
		if not pos_illnesses:
			return 1
		if not neg_illnesses:
			return 2


def build_tree(records, symptoms):
	"""
	The function builds a tree where each node is a question about a symptom
	in the order of the symptoms list.
	And each leaf is a disease that fits the symptoms according to the records.
	:param records: list of records objects.
	:param symptoms: list of symptoms
	:return:Diagnosed object with the root of the tree.
	"""
	_check_symptoms_and_records(records, symptoms)
	if len(symptoms) == 0:
		illnesses_lst = [record.illness for record in records]
		counter = collections.Counter(illnesses_lst)
		most_common = counter.most_common()
		root = Node(most_common[0][0])
		return Diagnoser(root)
	root = Node(symptoms[0], None, None)
	_create_symptoms_nodes(root, symptoms, 0)
	_add_leaves(records, root, [], [])
	return Diagnoser(root)


def _check_symptoms_and_records(records, symptoms):
	"""
	Checks if all the values in the record list symptoms list are valid.
	Raise an exception if some value is illegal
	:param records:list of records object
	:param symptoms:list of symptoms
	:return:None
	"""
	for symptom in symptoms:
		if type(symptom) != str:
			raise TypeError("Invalid symptom! symptoms can be strings only!")
	for record in records:
		if type(record) != Record:
			raise TypeError("Invalid Record! records can be Records only!")


def _create_symptoms_nodes(root, symptoms, idx):
	"""
	Creates a Node object for each symptom and inserts it into the tree.
	:param root:the root of the current tree
	:param symptoms:list of symptoms
	:param idx:the idx of the current symptom in the list
	:return:None
	"""
	if idx == len(symptoms) - 1:
		return
	root.positive_child = Node(symptoms[idx+1], None, None)
	root.negative_child = Node(symptoms[idx + 1], None, None)
	_create_symptoms_nodes(root.positive_child, symptoms, idx + 1)
	_create_symptoms_nodes(root.negative_child, symptoms, idx + 1)


def _add_leaves(records, root, positive_symptoms_lst, negative_symptoms_lst):
	"""
	For each leaf, check which diseases match to the symptoms according to the
	records, and put the most common disease into the leaf.
	If there is no suitable disease, insert None.
	:param records:list of records object
	:param root:the root of the current tree
	:param positive_symptoms_lst:A list of all the symptoms for which the
	answer was yes
	:param negative_symptoms_lst:A list of all the symptoms for which the
	answer was no
	:return:None
	"""
	if root.positive_child is None:
		candidates = records[:]
		for symptom in positive_symptoms_lst:
			for record in candidates[::-1]:
				if symptom not in record.symptoms:
					candidates.remove(record)
		for record in candidates[::-1]:
			for symptom in record.symptoms:
				if symptom in negative_symptoms_lst:
					candidates.remove(record)
					break
		pos_candidates = []
		neg_candidates = []
		for candidate in candidates:
			if root.data in candidate.symptoms:
				pos_candidates.append(candidate)
			else:
				neg_candidates.append(candidate)
		for lst in (pos_candidates, neg_candidates):
			illnesses_lst = [candidate.illness for candidate in lst]
			counter = collections.Counter(illnesses_lst)
			most_common = counter.most_common(1)
			if lst is pos_candidates:
				if not lst:
					root.positive_child = Node(None)
				else:
					root.positive_child = Node(most_common[0][0])
			else:
				if not lst:
					root.negative_child = Node(None)
				else:
					root.negative_child = Node(most_common[0][0])
		return None

	positive_symptoms_lst.append(root.data)
	_add_leaves(records, root.positive_child, positive_symptoms_lst,
				negative_symptoms_lst)
	positive_symptoms_lst.pop()
	negative_symptoms_lst.append(root.data)
	_add_leaves(records, root.negative_child, positive_symptoms_lst,
				negative_symptoms_lst)
	negative_symptoms_lst.pop()


def optimal_tree(records, symptoms, depth):
	"""
	Calculates the diagnosis success rate for each tree with 'depth' symptoms
	from the list of symptoms,
	and returns the tree with the highest success rate.
	:param records:list of records object
	:param symptoms:list of symptoms
	:param depth: int
	:return:Diagnoser object with the highest success rate.
	"""
	_check_symptoms_and_depth(depth, symptoms)
	_check_symptoms_and_records(records, symptoms)
	best_tree = ("some tree", 0)
	symptoms_combinations = list(combinations(symptoms, depth))
	for combination in symptoms_combinations:
		tree1 = build_tree(records, list(combination))
		success_rate = tree1.calculate_success_rate(records)
		if success_rate > best_tree[1]:
			best_tree = (tree1, success_rate)
	return best_tree[0]


def _check_symptoms_and_depth(depth, symptoms):
	"""
	Checks that the depth value and symptoms are valid,
	Raise an exception if some value is illegal
	:param depth: int
	:param symptoms: list of symptoms
	:return:None
	"""
	if depth < 0 or depth > len(symptoms):
		raise ValueError("Illegal depth value")
	for symptom_idx in range(len(symptoms)):
		for other_symptom in symptoms[symptom_idx+1:]:
			if symptoms[symptom_idx] == other_symptom:
				raise ValueError("The same symptom appears more than once!")
