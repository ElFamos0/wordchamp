<script setup>
import Letter from '@/components/Letter.vue';
import {defineProps, ref} from "vue"

const taillemot = ref(8);

const rowprop = defineProps({
    solution: Boolean,
    word: String,
    submitted: Boolean,
})

console.log(rowprop.solution); // to avoid unused variable warning

</script>

<template>
<b-container>
<b-row class="justify-content-md-center" style="font-size:50px;">
    <letter v-for="i in taillemot" :key="i" :letter=word[i-1]></letter>
</b-row>
</b-container>


</template>


<style scoped>

</style>