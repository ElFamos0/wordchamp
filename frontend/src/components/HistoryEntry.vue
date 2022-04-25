<template>
    <!-- id inutile ? -->
    <div @dblclick="$emit('show-details', entryId )" class="container">
        <div>(Id de la partie : {{entryId}})</div>
        <!-- <div>Solution : {{solution}}</div> -->
        <WordRow :solution="solution" :word="solution" submitted="true"/>
        <div>{{result}}</div>
    </div>
</template>


<script>
import WordRow from './WordRow.vue'
export default {
  name: 'HistoryEntry',
  props: {
    entryId : String,
    solution : String,
    result: String,
  },
  components: {
    WordRow
  },
  emits: ['show-details'],
}
</script>


<style scoped>
.container {
  margin: 10px auto;
  overflow: auto;
  border: 2px solid rgb(55, 16, 229);
  padding: 10px;
  border-radius: 5px;
}
</style>