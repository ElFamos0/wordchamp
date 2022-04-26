<script>
export default {
    name: 'choice-page',
    methods: { 
        onClick : function(i) {
            this.$router.push('/word/:'+(i+4))
        }       
    },
}
</script>

<template>
<div style="padding-top: 2%">
    <h1 style="font-family: 'Roboto', sans-serif">
        Choisis le nombre de lettres
    </h1>
    <v-container style="display: flex; justify-content: center">
        <div class="my-2" v-for="i in 5" :key="i" style="margin: 1%">
            <v-btn @click="onClick(i)" x-small color="primary">
                {{i+4}} lettres
            </v-btn>
        </div>
    </v-container>
</div>
</template>

<style scoped>
</style>